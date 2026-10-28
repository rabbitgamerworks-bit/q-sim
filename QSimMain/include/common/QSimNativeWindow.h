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
#ifndef __QSimNativeWindow_H__
#define __QSimNativeWindow_H__

#include <OgreCommon.h>
#include <OgreRenderWindow.h>
#include <OgreRoot.h>
#include <OgreWindowEventUtilities.h>

namespace QSim
{
    /**
     * Creates the operating system windows Ogre renders into.
     *
     * Unlike the old OpenGL render system, Ogre's Vulkan render system does
     * not create windows itself, it only renders into an existing window
     * passed as "externalWindowHandle". This creates a plain native window
     * (Xlib on Linux, Win32 on Windows) which leaves keyboard and mouse
     * handling to OIS, and reports close/resize events to
     * OgreBites::WindowEventListener instances.
     */
    class NativeWindow
    {
    public:
        /// Creates a native window and an Ogre::RenderWindow rendering into it.
        static Ogre::RenderWindow* createRenderWindow( Ogre::Root& root
                                                     , const Ogre::String& title
                                                     , unsigned int width
                                                     , unsigned int height
                                                     , bool full_screen = false
                                                     , const Ogre::NameValuePairList* misc_params = nullptr
                                                     , bool hidden = false );

        /// Creates a window as configured by the render system options (ogre.cfg).
        static Ogre::RenderWindow* createConfiguredRenderWindow( Ogre::Root& root
                                                               , const Ogre::String& title
                                                               , bool hidden = false );

        /// Native handle (X11 Window / HWND) of the window, as needed by OIS.
        static size_t getHandle( Ogre::RenderWindow* window );

        /// Destroys the native window of an Ogre render window.
        static void destroyRenderWindow( Ogre::RenderWindow* window );

        /// Processes the window system events, call once per frame.
        static void messagePump();

        static void addWindowEventListener( Ogre::RenderWindow* window, OgreBites::WindowEventListener* listener );
        static void removeWindowEventListener( Ogre::RenderWindow* window, OgreBites::WindowEventListener* listener );
    };
}

#endif // __QSimNativeWindow_H__
