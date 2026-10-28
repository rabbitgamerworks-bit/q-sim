/*
-----------------------------------------------------------------------------
This file is part of Q-Sim

Q-Sim is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 2.0 (GPLv2) of the License.

Q-Sim is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
-----------------------------------------------------------------------------
*/
#include "common/QSimNativeWindow.h"

#include <algorithm>
#include <map>
#include <vector>

#include <OgreException.h>
#include <OgreLogManager.h>
#include <OgreRenderSystem.h>
#include <OgreStringConverter.h>

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#   ifndef WIN32_LEAN_AND_MEAN
#       define WIN32_LEAN_AND_MEAN
#   endif
#   ifndef NOMINMAX
#       define NOMINMAX
#   endif
#   include <windows.h>
#elif OGRE_PLATFORM == OGRE_PLATFORM_LINUX
#   include <X11/Xlib.h>
#   include <X11/Xutil.h>
#   include <X11/Xatom.h>
#endif

namespace QSim
{
    namespace
    {
        struct WindowData
        {
            size_t                                          handle = 0;
            std::vector<OgreBites::WindowEventListener*>    listeners;
        };

        std::map<Ogre::RenderWindow*, WindowData>& windows()
        {
            static std::map<Ogre::RenderWindow*, WindowData> s_windows;
            return s_windows;
        }

        Ogre::RenderWindow* findWindow( size_t handle )
        {
            for( auto& entry : windows() )
            {
                if( entry.second.handle == handle )
                {
                    return entry.first;
                }
            }
            return nullptr;
        }

        //----------------------------------------------------------------------
        void notifyResized( size_t handle, unsigned int width, unsigned int height )
        {
            Ogre::RenderWindow* window( findWindow( handle ) );
            if( window == nullptr || width == 0 || height == 0
                || ( window->getWidth() == width && window->getHeight() == height ) )
            {
                return;
            }
            window->resize( width, height );
            const auto listeners( windows()[ window ].listeners );
            for( auto* listener : listeners )
            {
                listener->windowResized( window );
            }
        }

        //----------------------------------------------------------------------
        void notifyClosing( size_t handle )
        {
            Ogre::RenderWindow* window( findWindow( handle ) );
            if( window == nullptr )
            {
                return;
            }
            bool close( true );
            const auto listeners( windows()[ window ].listeners );
            for( auto* listener : listeners )
            {
                close = listener->windowClosing( window ) && close;
            }
            if( close )
            {
                for( auto* listener : listeners )
                {
                    listener->windowClosed( window );
                }
            }
        }

#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX
        //----------------------------------------------------------------------
        Display* display()
        {
            static Display* s_display( XOpenDisplay( nullptr ) );
            if( s_display == nullptr )
            {
                OGRE_EXCEPT( Ogre::Exception::ERR_RENDERINGAPI_ERROR
                  , "Could not open the X display, is DISPLAY set?"
                  , "QSim::NativeWindow" );
            }
            return s_display;
        }

        Atom deleteWindowAtom()
        {
            static Atom s_atom( XInternAtom( display(), "WM_DELETE_WINDOW", False ) );
            return s_atom;
        }

        //----------------------------------------------------------------------
        size_t createNativeWindow( const Ogre::String& title, unsigned int width, unsigned int height
                                 , bool full_screen, bool hidden )
        {
            Display* dpy( display() );
            const int screen( DefaultScreen( dpy ) );
            if( full_screen )
            {
                width = static_cast<unsigned int>( DisplayWidth( dpy, screen ) );
                height = static_cast<unsigned int>( DisplayHeight( dpy, screen ) );
            }

            XSetWindowAttributes attributes {};
            attributes.background_pixel = BlackPixel( dpy, screen );
            // Only window management events here: keyboard and mouse are read by OIS,
            // X11 allows a single client to select button presses on a window.
            attributes.event_mask = StructureNotifyMask | ExposureMask;
            Window window( XCreateWindow( dpy, RootWindow( dpy, screen ), 0, 0, width, height, 0
                , CopyFromParent, InputOutput, CopyFromParent, CWBackPixel | CWEventMask, &attributes ) );

            XStoreName( dpy, window, title.c_str() );
            Atom delete_atom( deleteWindowAtom() );
            XSetWMProtocols( dpy, window, &delete_atom, 1 );

            if( full_screen )
            {
                Atom wm_state( XInternAtom( dpy, "_NET_WM_STATE", False ) );
                Atom fullscreen_atom( XInternAtom( dpy, "_NET_WM_STATE_FULLSCREEN", False ) );
                XChangeProperty( dpy, window, wm_state, XA_ATOM, 32, PropModeReplace
                    , reinterpret_cast<unsigned char*>( &fullscreen_atom ), 1 );
            }

            if( !hidden )
            {
                XMapWindow( dpy, window );
                // wait until the window is visible, the swapchain needs its real size
                XEvent event;
                do
                {
                    XWindowEvent( dpy, window, StructureNotifyMask, &event );
                }
                while( event.type != MapNotify );
            }
            XFlush( dpy );
            return static_cast<size_t>( window );
        }

        //----------------------------------------------------------------------
        void destroyNativeWindow( size_t handle )
        {
            XDestroyWindow( display(), static_cast<Window>( handle ) );
            XFlush( display() );
        }

        //----------------------------------------------------------------------
        void pumpNativeEvents()
        {
            if( windows().empty() )
            {
                return;
            }
            Display* dpy( display() );
            while( XPending( dpy ) > 0 )
            {
                XEvent event;
                XNextEvent( dpy, &event );
                switch( event.type )
                {
                    case ConfigureNotify:
                        notifyResized( static_cast<size_t>( event.xconfigure.window )
                            , static_cast<unsigned int>( event.xconfigure.width )
                            , static_cast<unsigned int>( event.xconfigure.height ) );
                        break;
                    case ClientMessage:
                        if( static_cast<Atom>( event.xclient.data.l[ 0 ] ) == deleteWindowAtom() )
                        {
                            notifyClosing( static_cast<size_t>( event.xclient.window ) );
                        }
                        break;
                    default:
                        break;
                }
            }
        }
#elif OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        //----------------------------------------------------------------------
        LRESULT CALLBACK windowProc( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam )
        {
            switch( message )
            {
                case WM_CLOSE:
                    // let the listeners decide, the window is destroyed with the render window
                    notifyClosing( reinterpret_cast<size_t>( hwnd ) );
                    return 0;
                case WM_SIZE:
                    notifyResized( reinterpret_cast<size_t>( hwnd ), LOWORD( lparam ), HIWORD( lparam ) );
                    return 0;
                default:
                    return DefWindowProcA( hwnd, message, wparam, lparam );
            }
        }

        const char* const WINDOW_CLASS_NAME = "QSimWindow";

        //----------------------------------------------------------------------
        size_t createNativeWindow( const Ogre::String& title, unsigned int width, unsigned int height
                                 , bool full_screen, bool hidden )
        {
            HINSTANCE instance( GetModuleHandleA( nullptr ) );
            static bool s_registered( false );
            if( !s_registered )
            {
                WNDCLASSEXA window_class {};
                window_class.cbSize = sizeof( window_class );
                window_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
                window_class.lpfnWndProc = windowProc;
                window_class.hInstance = instance;
                window_class.hCursor = LoadCursor( nullptr, IDC_ARROW );
                window_class.lpszClassName = WINDOW_CLASS_NAME;
                RegisterClassExA( &window_class );
                s_registered = true;
            }

            DWORD style( full_screen ? WS_POPUP : WS_OVERLAPPEDWINDOW );
            if( full_screen )
            {
                width = static_cast<unsigned int>( GetSystemMetrics( SM_CXSCREEN ) );
                height = static_cast<unsigned int>( GetSystemMetrics( SM_CYSCREEN ) );
            }
            RECT rect { 0, 0, static_cast<LONG>( width ), static_cast<LONG>( height ) };
            AdjustWindowRect( &rect, style, FALSE );

            HWND hwnd( CreateWindowExA( 0, WINDOW_CLASS_NAME, title.c_str(), style
                , full_screen ? 0 : CW_USEDEFAULT, full_screen ? 0 : CW_USEDEFAULT
                , rect.right - rect.left, rect.bottom - rect.top
                , nullptr, nullptr, instance, nullptr ) );
            if( hwnd == nullptr )
            {
                OGRE_EXCEPT( Ogre::Exception::ERR_RENDERINGAPI_ERROR, "CreateWindowEx failed", "QSim::NativeWindow" );
            }
            if( !hidden )
            {
                ShowWindow( hwnd, SW_SHOW );
                UpdateWindow( hwnd );
            }
            return reinterpret_cast<size_t>( hwnd );
        }

        //----------------------------------------------------------------------
        void destroyNativeWindow( size_t handle )
        {
            DestroyWindow( reinterpret_cast<HWND>( handle ) );
        }

        //----------------------------------------------------------------------
        void pumpNativeEvents()
        {
            MSG message;
            while( PeekMessageA( &message, nullptr, 0, 0, PM_REMOVE ) )
            {
                TranslateMessage( &message );
                DispatchMessageA( &message );
            }
        }
#else
        size_t createNativeWindow( const Ogre::String&, unsigned int, unsigned int, bool, bool )
        {
            OGRE_EXCEPT( Ogre::Exception::ERR_NOT_IMPLEMENTED
              , "Creating windows for the Vulkan render system is only implemented for Linux (X11) and Windows"
              , "QSim::NativeWindow" );
        }

        void destroyNativeWindow( size_t ) {}
        void pumpNativeEvents() {}
#endif
    }

    //--------------------------------------------------------------------------
    Ogre::RenderWindow*
    NativeWindow::createRenderWindow( Ogre::Root& root
                                    , const Ogre::String& title
                                    , unsigned int width
                                    , unsigned int height
                                    , bool full_screen
                                    , const Ogre::NameValuePairList* misc_params
                                    , bool hidden )
    {
        Ogre::NameValuePairList params;
        if( misc_params != nullptr )
        {
            params = *misc_params;
        }

        size_t handle( 0 );
        auto external( params.find( "externalWindowHandle" ) );
        if( external != params.end() )
        {
            // the caller already owns a window (e.g. a Qt widget)
            handle = Ogre::StringConverter::parseSizeT( external->second );
        }
        else
        {
            handle = createNativeWindow( title, width, height, full_screen, hidden );
            params[ "externalWindowHandle" ] = Ogre::StringConverter::toString( handle );
        }

        // the native window already has the screen size when full screen
        Ogre::RenderWindow* window( root.createRenderWindow( title, width, height, false, &params ) );
        windows()[ window ].handle = handle;
        return window;
    }

    //--------------------------------------------------------------------------
    Ogre::RenderWindow*
    NativeWindow::createConfiguredRenderWindow( Ogre::Root& root, const Ogre::String& title, bool hidden )
    {
        Ogre::RenderWindowDescription desc( root.getRenderSystem()->getRenderWindowDescription() );
        if( desc.width == 0 || desc.height == 0 )
        {
            desc.width = 800;
            desc.height = 600;
        }
        return createRenderWindow( root, title, desc.width, desc.height, desc.useFullScreen, &desc.miscParams, hidden );
    }

    //--------------------------------------------------------------------------
    size_t
    NativeWindow::getHandle( Ogre::RenderWindow* window )
    {
        auto it( windows().find( window ) );
        if( it == windows().end() )
        {
            // a window created by another render system
            size_t handle( 0 );
            window->getCustomAttribute( "WINDOW", &handle );
            return handle;
        }
        return it->second.handle;
    }

    //--------------------------------------------------------------------------
    void
    NativeWindow::destroyRenderWindow( Ogre::RenderWindow* window )
    {
        auto it( windows().find( window ) );
        if( it == windows().end() )
        {
            return;
        }
        const size_t handle( it->second.handle );
        windows().erase( it );
        Ogre::Root::getSingleton().destroyRenderTarget( window );
        destroyNativeWindow( handle );
    }

    //--------------------------------------------------------------------------
    void
    NativeWindow::messagePump()
    {
        pumpNativeEvents();
        // windows created by the render system itself (GL)
        OgreBites::WindowEventUtilities::messagePump();
    }

    //--------------------------------------------------------------------------
    void
    NativeWindow::addWindowEventListener( Ogre::RenderWindow* window, OgreBites::WindowEventListener* listener )
    {
        auto it( windows().find( window ) );
        if( it == windows().end() )
        {
            OgreBites::WindowEventUtilities::addWindowEventListener( window, listener );
            return;
        }
        it->second.listeners.push_back( listener );
    }

    //--------------------------------------------------------------------------
    void
    NativeWindow::removeWindowEventListener( Ogre::RenderWindow* window, OgreBites::WindowEventListener* listener )
    {
        auto it( windows().find( window ) );
        if( it == windows().end() )
        {
            OgreBites::WindowEventUtilities::removeWindowEventListener( window, listener );
            return;
        }
        auto& listeners( it->second.listeners );
        listeners.erase( std::remove( listeners.begin(), listeners.end(), listener ), listeners.end() );
    }

    //--------------------------------------------------------------------------
}
