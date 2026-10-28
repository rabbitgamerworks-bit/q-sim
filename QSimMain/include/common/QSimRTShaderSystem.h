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
#ifndef __QSimRTShaderSystem_H__
#define __QSimRTShaderSystem_H__

#include <cstdlib>
#include <memory>

#include <OgreBitesConfigDialog.h>
#include <OgreLogManager.h>
#include <OgreMaterialManager.h>
#include <OgreRTShaderSystem.h>
#include <OgreResourceGroupManager.h>
#include <OgreRoot.h>
#include <OgreSGTechniqueResolverListener.h>
#include <OgreViewport.h>

#include "qsim_version.h"

/**
 * Helpers shared by the game and the utilities to run on the Vulkan render
 * system. Vulkan has no fixed function pipeline, so the RT Shader System
 * generates shaders for all fixed function style materials.
 */
namespace QSim
{
    namespace RTShaderSystem
    {
        static const char* const RENDER_SYSTEM_VULKAN = "Vulkan Rendering Subsystem";

        //----------------------------------------------------------------------
        inline std::unique_ptr<OgreBites::SGTechniqueResolverListener>& techniqueResolver()
        {
            static std::unique_ptr<OgreBites::SGTechniqueResolverListener> resolver;
            return resolver;
        }

        //----------------------------------------------------------------------
        /// Loads the Vulkan render system, the GLSLang program manager it
        /// needs and the image codecs, for tools that do not read a plugins.cfg.
        inline void loadVulkanPlugins( Ogre::Root& root )
        {
            Ogre::String plugin_dir( QSIM_OGRE_PLUGIN_DIR );
            if( const char* env_plugin_dir = std::getenv( "QSIM_OGRE_PLUGIN_DIR" ) )
            {
                plugin_dir = env_plugin_dir;
            }
            const Ogre::String suffix( OGRE_BUILD_SUFFIX );
            for( const char* plugin : { "RenderSystem_Vulkan", "Plugin_GLSLangProgramManager", "Codec_STBI" } )
            {
                root.loadPlugin( plugin_dir + "/" + plugin + suffix );
            }
        }

        //----------------------------------------------------------------------
        /// Picks a render system: restored config, the native dialog, or Vulkan.
        inline bool configureRenderSystem( Ogre::Root& root, bool show_dialog )
        {
            if( !show_dialog && root.restoreConfig() )
            {
                return true;
            }

            if( show_dialog )
            {
                if( Ogre::ConfigDialog* dialog = OgreBites::getNativeConfigDialog() )
                {
                    return root.showConfigDialog( dialog );
                }
            }

            Ogre::RenderSystem* render_system( root.getRenderSystemByName( RENDER_SYSTEM_VULKAN ) );
            if( render_system == nullptr )
            {
                const Ogre::RenderSystemList& available( root.getAvailableRenderers() );
                if( available.empty() )
                {
                    Ogre::LogManager::getSingleton().logError( "No render system plugin loaded, check plugins.cfg" );
                    return false;
                }
                render_system = available.front();
                Ogre::LogManager::getSingleton().logWarning( Ogre::String( RENDER_SYSTEM_VULKAN )
                    + " not available, falling back to " + render_system->getName() );
            }
            root.setRenderSystem( render_system );
            root.saveConfig();
            return true;
        }

        //----------------------------------------------------------------------
        /// Call after Root::initialise, before any material gets loaded.
        inline void initialise()
        {
            Ogre::String media_dir( QSIM_OGRE_MEDIA_DIR );
            if( const char* env_media_dir = std::getenv( "QSIM_OGRE_MEDIA_DIR" ) )
            {
                media_dir = env_media_dir;
            }

            Ogre::ResourceGroupManager& rgm( Ogre::ResourceGroupManager::getSingleton() );
            rgm.addResourceLocation( media_dir + "/Main", "FileSystem", Ogre::RGN_INTERNAL );
            rgm.addResourceLocation( media_dir + "/RTShaderLib", "FileSystem", Ogre::RGN_INTERNAL );

            if( !Ogre::RTShader::ShaderGenerator::initialize() )
            {
                OGRE_EXCEPT( Ogre::Exception::ERR_INTERNAL_ERROR
                  , "Failed to initialise the RT Shader System, check that " + media_dir
                    + " contains the OGRE media (or set QSIM_OGRE_MEDIA_DIR)"
                  , "QSim::RTShaderSystem::initialise" );
            }

            auto& resolver( techniqueResolver() );
            resolver = std::make_unique<OgreBites::SGTechniqueResolverListener>(
                Ogre::RTShader::ShaderGenerator::getSingletonPtr() );
            Ogre::MaterialManager::getSingleton().addListener( resolver.get() );
        }

        //----------------------------------------------------------------------
        inline void registerSceneManager( Ogre::SceneManager* scene_manager )
        {
            if( auto* shader_generator = Ogre::RTShader::ShaderGenerator::getSingletonPtr() )
            {
                shader_generator->addSceneManager( scene_manager );
            }
        }

        //----------------------------------------------------------------------
        /// Makes the viewport use the RTSS generated techniques.
        inline void registerViewport( Ogre::Viewport* viewport )
        {
            viewport->setMaterialScheme( Ogre::MSN_SHADERGEN );
        }

        //----------------------------------------------------------------------
        /// Call before deleting Ogre::Root.
        inline void shutdown()
        {
            auto& resolver( techniqueResolver() );
            if( resolver )
            {
                if( Ogre::MaterialManager::getSingletonPtr() )
                {
                    Ogre::MaterialManager::getSingleton().removeListener( resolver.get() );
                }
                resolver.reset();
            }
            if( Ogre::RTShader::ShaderGenerator::getSingletonPtr() )
            {
                Ogre::RTShader::ShaderGenerator::destroy();
            }
        }
    }
}

#endif // __QSimRTShaderSystem_H__
