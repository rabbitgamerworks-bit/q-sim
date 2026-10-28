#include "common/QSimNativeWindow.h"
#include "OgreBase.h"
#include <OgreFontManager.h>
#include "common/QSimRTShaderSystem.h"
#include "common/QSimLegacyScripts.h"

Ogre::Root*                     root;
Ogre::RenderWindow*             window;
std::vector< Ogre::Entity* >    entitys;
Ogre::Camera                   *camera;
DisplayFrameListener           *frame_listener;
Ogre::OverlaySystem            *overlay_system;

void
InitializeOgreBase( const Ogre::String& name )
{
    Ogre::LogManager* log_manager = new Ogre::LogManager();
    log_manager->createLog( "q-sim.log", true, true );
    log_manager->getDefaultLog()->setLogDetail( ( Ogre::LoggingLevel )3 );

    Ogre::String ressource_cfg("");
    Ogre::String plugins_cfg("");

#ifdef NDEBUG
    ressource_cfg = "resources.cfg";
    plugins_cfg = "plugins.cfg";
#else
    ressource_cfg = "resources_d.cfg";
    plugins_cfg = "plugins_d.cfg";
#endif

    // init root early
    root = new Ogre::Root( plugins_cfg );
    // exported data may still use the Ogre 1.4 mesh format
    Ogre::MeshSerializer::enablePre1_8Formats( true );

    // set up resources
    // Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load( ressource_cfg );

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    Ogre::ResourceGroupManager &res_gm( Ogre::ResourceGroupManager::getSingleton() );
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            res_gm.addResourceLocation( archName, typeName, secName, true );
        }
    }

    // configure: saved config or Vulkan by default
    if( !QSim::RTShaderSystem::configureRenderSystem( *root, false ) )
    {
        OGRE_EXCEPT( Ogre::Exception::ERR_RENDERINGAPI_ERROR, "No render system available", "InitializeOgreBase" );
    }

    root->initialise( false );
    Ogre::NameValuePairList misc;
    misc[ "title" ] = name;
    window = QSim::NativeWindow::createRenderWindow( *root, name, 800, 600, false, &misc );
    QSim::RTShaderSystem::initialise();
    QSim::LegacyScriptListener::install();


    // initialize resource
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation( "./", "FileSystem", "General" );
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation( "./exported", "FileSystem", "General" );
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    Ogre::SceneManager* scene_manager;
    Ogre::Viewport*     viewport;

    // creates the FontManager and OverlayManager
    overlay_system = new Ogre::OverlaySystem();

    frame_listener = new DisplayFrameListener( window );
    root->addFrameListener( frame_listener );

    scene_manager = root->createSceneManager( Ogre::SMT_DEFAULT, "Scene" );
    scene_manager->addRenderQueueListener( overlay_system );
    QSim::RTShaderSystem::registerSceneManager( scene_manager );
    scene_manager->clearScene();
    scene_manager->setAmbientLight( Ogre::ColourValue( 0.5, 0.5, 0.5 ) );
    Ogre::Light* directionalLight = scene_manager->createLight("directionalLight");
    directionalLight->setType( Ogre::Light::LT_DIRECTIONAL );
    directionalLight->setDiffuseColour( Ogre::ColourValue( 0.5, 0.5, 0.5) );
    directionalLight->setSpecularColour( Ogre::ColourValue( 0.5, 0.5, 0.5) );
    // Since Ogre 1.10 lights take their direction from their scene node
    Ogre::SceneNode* light_node = scene_manager->getRootSceneNode()->createChildSceneNode();
    light_node->attachObject(directionalLight);
    light_node->setDirection(Ogre::Vector3( 0, 0, -1 ), Ogre::Node::TS_WORLD);

    camera = scene_manager->createCamera( "Camera" );
    camera->setNearClipDistance( 0.01f );
    Ogre::SceneNode* camera_node = scene_manager->getRootSceneNode()->createChildSceneNode( "CameraNode" );
    camera_node->setFixedYawAxis( true );
    camera_node->attachObject( camera );
    camera_node->setPosition( 0, 5, 10 );
    camera_node->lookAt( Ogre::Vector3( 0, 0, 0 ), Ogre::Node::TS_WORLD );

    viewport = window->addViewport( camera );
    QSim::RTShaderSystem::registerViewport( viewport );
    viewport->setBackgroundColour( Ogre::ColourValue( 0.0f, 0.4f, 0.0f ) );
    camera->setAspectRatio( Ogre::Real( viewport->getActualWidth() ) / Ogre::Real( viewport->getActualHeight() ) );

    LOGGER = new Logger( "game.log" );
}



void
DeinitializeOgreBase()
{
    delete LOGGER;

    delete frame_listener;
    frame_listener = nullptr;
    QSim::RTShaderSystem::shutdown();
    delete overlay_system;
    overlay_system = nullptr;
    delete root;
}
