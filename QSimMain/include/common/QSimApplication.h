/*
-----------------------------------------------------------------------------
Copyright (c) 19.10.2013 Tobias Peters <tobias.peters@kreativeffekt.at>

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
#ifndef __QSimApplication_H__
#define __QSimApplication_H__

#include <OgreRoot.h>
#include <OgreOverlaySystem.h>
#include <memory>
#include "TypeDefine.h"

namespace QSim
{
    class Application : public Ogre::Singleton<Application>
    {
    public:
        Application(Ogre::String pluginsFileName, Ogre::String resourcesFile, Ogre::String logFileName)
            : m_plugins_filename(pluginsFileName), m_resources_filename(resourcesFile), m_log_filename(logFileName)
        {

        }
        Application( int argc, char *argv[] );
        virtual ~Application();
        bool                initOgre( bool hideWindow = false );
        Ogre::Root*         getRoot( void );
        Ogre::RenderWindow* getRenderWindow( void );
        Ogre::OverlaySystem* getOverlaySystem( void ) { return m_overlay_system.get(); }
        const String&       getResourcesFilename( void );
        Ogre::ResourceGroupManager* ResMgr() { return mResMgr; }

        /// Lets the RT Shader System generate shaders for this scene manager
        static void         registerSceneManager( Ogre::SceneManager* scene_manager );
    protected:
        String  getWindowTitle( void ) const;
        bool    processCommandLine( int argc, char *argv[] );
        bool    configureRenderSystem( void );
        void    initShaderGenerator( void );
        void    registerArchiveFactories( void );
        void    loadResourcesConfig( void );
        void    initComponents( void );
        void    destroyComponents( void );
        void    createResourceManagers( void );
        void    destroyResourceManagers( void );

    private:
        typedef std::vector<std::shared_ptr<Ogre::ResourceManager>> ResourceManagerVector;


        static const char*      CLI_SECTION_GENERIC;
        static const char*      CLI_HELP;
        static const char*      CLI_HELP_DESCRIPTION;
        static const char*      CLI_CONFIG_FILE;
        static const char*      CLI_CONFIG_FILE_DESCRIPTION;
        static const char*      CLI_LOG_FILE;
        static const char*      CLI_LOG_FILE_DESCRIPTION;
        static const char*      CLI_PLUGINS_FILE;
        static const char*      CLI_PLUGINS_FILE_DESCRIPTION;
        static const char*      CLI_RESOURCES_FILE;
        static const char*      CLI_RESOURCES_FILE_DESCRIPTION;
        static const char*      CLI_CONFIG_DIALOG;
        static const char*      CLI_CONFIG_DIALOG_DESCRIPTION;

        int     m_argc = 0;
        char  **m_argv = nullptr;
        String  m_config_filename;
        String  m_log_filename;
        String  m_plugins_filename;
        String  m_resources_filename;

        bool m_initialized = false;
        bool m_show_config_dialog = false;
        std::unique_ptr<Ogre::Root> m_root;
        std::unique_ptr<Ogre::OverlaySystem> m_overlay_system;
        Ogre::RenderWindow* m_render_window = nullptr; // Not owned
        ResourceManagerVector m_resource_managers;
        Ogre::ResourceGroupManager* mResMgr = nullptr; // Not owned
    };
}

#endif // __QSimApplication_H__
