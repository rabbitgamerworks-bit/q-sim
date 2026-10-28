/*
-----------------------------------------------------------------------------
Copyright (c) 26.10.2013 Tobias Peters <tobias.peters@kreativeffekt.at>

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
#include "common/QSimRTShaderSystem.h"
#include "QSimUtility.h"

namespace QSim
{
    //--------------------------------------------------------------------------
    Utility::Utility(int argc, char *argv[]) :
        Application( argc, argv )
      , m_frame_listener( NULL )
      , m_scene_manager( NULL )
      , m_camera( NULL )
      , m_viewport( NULL )
    {
    }

    //--------------------------------------------------------------------------
    Utility::~Utility()
    {
    }

    //--------------------------------------------------------------------------
    Ogre::Camera*
    Utility::getCamera()
    {
        return m_camera;
    }

    //--------------------------------------------------------------------------
    void
    Utility::initComponents()
    {
        Application::initComponents();
        Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

        Ogre::Root         *root( getRoot() );

        m_scene_manager = root->createSceneManager(Ogre::SMT_DEFAULT, "Scene" );
        m_scene_manager->addRenderQueueListener( getOverlaySystem() );
        registerSceneManager( m_scene_manager );
        m_scene_manager->clearScene();
        m_scene_manager->setAmbientLight( Ogre::ColourValue( 0.5, 0.5, 0.5 ) );
        Ogre::Light* directionalLight = m_scene_manager->createLight("directionalLight");
        directionalLight->setType( Ogre::Light::LT_DIRECTIONAL );
        directionalLight->setDiffuseColour( Ogre::ColourValue( 0.5, 0.5, 0.5) );
        directionalLight->setSpecularColour( Ogre::ColourValue( 0.5, 0.5, 0.5) );
        // Since Ogre 1.10 lights take their direction from their scene node
        Ogre::SceneNode* light_node = m_scene_manager->getRootSceneNode()->createChildSceneNode();
        light_node->attachObject(directionalLight);
        light_node->setDirection(Ogre::Vector3( 0, 0, -1 ), Ogre::Node::TS_WORLD);

        m_camera = m_scene_manager->createCamera( "Camera" );
        m_camera->setNearClipDistance( 0.01f );
        Ogre::SceneNode* camera_node = m_scene_manager->getRootSceneNode()->createChildSceneNode( "CameraNode" );
        camera_node->setFixedYawAxis( true );
        camera_node->attachObject( m_camera );
        camera_node->setPosition( 0, 5, 10 );
        camera_node->lookAt( Ogre::Vector3( 0, 0, 0 ), Ogre::Node::TS_WORLD );

        Ogre::RenderWindow *window( getRenderWindow() );
        m_viewport = window->addViewport( m_camera );
        RTShaderSystem::registerViewport( m_viewport );
        m_viewport->setBackgroundColour( Ogre::ColourValue( 0.0f, 0.4f, 0.0f ) );
        m_camera->setAspectRatio( Ogre::Real( m_viewport->getActualWidth() ) / Ogre::Real( m_viewport->getActualHeight() ) );

        m_frame_listener = new DisplayFrameListener( window );
        m_frame_listener->setCamera( m_camera );
        root->addFrameListener( m_frame_listener );
    }

    //--------------------------------------------------------------------------
    void
    Utility::destroyComponents()
    {
        delete m_frame_listener;
        m_frame_listener = NULL;
        Application::destroyComponents();
    }

    //--------------------------------------------------------------------------
}
