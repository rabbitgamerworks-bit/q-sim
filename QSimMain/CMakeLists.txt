# define header and source files for the library
set(HEADER_FILES
  include/modules/worldmap/WorldMapModule.h

  include/common/QSimManualObject.h
  include/common/QSimResource.h
  include/common/QSimStringUtil.h
  include/common/TypeDefine.h
  include/common/LzsFile.h
  include/common/File.h
  include/common/FileSystem.h
  include/common/make_unique.h
  include/map/QSimBackground2DFile.h
  include/map/QSimBackground2DFileManager.h
  include/map/QSimBackground2DFileXMLSerializer.h
  include/map/QSimTile.h
  include/map/QSimMapFile.h
  include/map/QSimMapFileManager.h
  include/map/QSimMapFileXMLSerializer.h
  include/map/QSimWalkmeshFile.h
  include/map/QSimWalkmeshFileManager.h
  include/map/QSimWalkmeshFileXMLSerializer.h
  include/LuaIncludes.h
  include/QSimGameState.h
  include/QSimPrerequisites.h
  include/core/particles/emitters/ParticlePointEmitter.h
  include/core/particles/emitters/ParticlePointEmitterFactory.h
  include/core/particles/renderer/ParticleEntityAdditionalData.h
  include/core/particles/renderer/ParticleEntityRenderer.h
  include/core/particles/renderer/ParticleEntityRendererDictionary.h
  include/core/particles/renderer/ParticleEntityRendererFactory.h
  include/core/particles/Particle.h
  include/core/particles/ParticleAdditionalData.h
  include/core/particles/ParticleEmitter.h
  include/core/particles/ParticleEmitterDictionary.h
  include/core/particles/ParticleEmitterFactory.h
  include/core/particles/ParticleEmitterTranslator.h
  include/core/particles/ParticlePool.h
  include/core/particles/ParticlePoolMap.h
  include/core/particles/ParticleRenderer.h
  include/core/particles/ParticleRendererFactory.h
  include/core/particles/ParticleRendererTranslator.h
  include/core/particles/ParticleSystem.h
  include/core/particles/ParticleSystemFactory.h
  include/core/particles/ParticleSystemManager.h
  include/core/particles/ParticleSystemTranslator.h
  include/core/particles/ParticleSystemTranslatorManager.h
  include/core/particles/ParticleTechnique.h
  include/core/particles/ParticleTechniqueTranslator.h
  include/core/particles/ParticleVisual.h
  include/core/Assert.h
  include/core/Background2D.h
  include/core/Background2DAnimation.h
  include/core/CameraManager.h
  include/core/CameraManagerCommands.h
  include/core/ConfigCmd.h
  include/core/ConfigCmdManager.h
  include/core/ConfigCmdManagerCommands.h
  include/core/ConfigFile.h
  include/core/ConfigVar.h
  include/core/ConfigVarManager.h
  include/core/Console.h
  include/core/DebugDraw.h
  include/core/Entity.h
  include/core/EntityCollision.h
  include/core/EntityDirection.h
  include/core/EntityManager.h
  include/core/EntityModel.h
  include/core/EntityPoint.h
  include/core/EntityTrigger.h
  include/core/Event.h
  include/core/GameFrameListner.h
  include/core/InputManager.h
  include/core/InputManagerCommands.h
  include/core/Logger.h
  include/core/Module.h
  include/core/ScriptManager.h
  include/core/ScriptManagerBinds.h
  include/core/ScriptManagerCommands.h
  include/core/Timer.h
  include/core/UiAnimation.h
  include/core/UiFont.h
  include/core/UiManager.h
  include/core/UiSprite.h
  include/core/UiTextArea.h
  include/core/UiWidget.h
  include/core/Utilites.h
  include/core/Walkmesh.h
  include/core/XmlBackground2DFile.h
  include/core/XmlFile.h
  include/core/XmlFontFile.h
  include/core/XmlFontsFile.h
  include/core/XmlMapFile.h
  #include/core/XmlMapsFile.h
  include/core/XmlPrototypesFile.h
  include/core/XmlScreenFile.h
  include/core/XmlScreensFile.h
  include/core/XmlScriptsFile.h
  include/core/XmlTextFile.h
  include/core/XmlTextsFile.h
  include/core/DialogsManager.h
  include/core/ScriptManagerBinds.h
  include/core/TextManager.h
  include/core/TextManagerCommands.h
  #include/viewer/ViewerModule.h
  include/data/QSimXMLSerializer.h
)

set(HEADER_FILES_DATA
  include/common/QSimApplication.h
include/data/worldmap/MapFile.h
  include/data/worldmap/MapFileManager.h
  include/data/worldmap/MapFileSerializer.h
  include/data/worldmap/TxzFile.h
  include/data/worldmap/TxzFileManager.h
  include/data/worldmap/TxzFileSerializer.h
  include/data/QSimAFile.h
  include/data/QSimAFileManager.h
  include/data/QSimAFileSerializer.h
  include/data/QSimBackgroundFile.h
  include/data/QSimBackgroundFileManager.h
  include/data/QSimBackgroundFileSerializer.h
  include/data/QSimBackgroundTextureLoader.h
  include/data/QSimCameraMatrixFile.h
  include/data/QSimCameraMatrixFileManager.h
  include/data/QSimCameraMatrixFileSerializer.h
  include/data/QSimFLevelBackground2DLoader.h
  include/data/QSimFLevelFile.h
  include/data/QSimFLevelFileManager.h
  include/data/QSimFLevelFileSerializer.h
  include/data/QSimFLevelTextureLoader.h
  include/data/QSimHRCFile.h
  include/data/QSimHRCFileManager.h
  include/data/QSimHRCFileSerializer.h
  include/data/QSimHRCMeshLoader.h
  include/data/QSimHRCSkeletonLoader.h
  include/data/QSimLGPArchive.h
  include/data/QSimLGPArchiveFactory.h
  include/data/QSimLGPArchiveSerializer.h
  include/data/QSimLZSDataStream.h
  include/data/QSimLZSFLevelFile.h
  include/data/QSimLZSFLevelFileManager.h
  include/data/QSimPaletteFile.h
  include/data/QSimPaletteFileManager.h
  include/data/QSimPaletteFileSerializer.h
  include/data/QSimPFile.h
  include/data/QSimPFileManager.h
  include/data/QSimPFileSerializer.h
  include/data/QSimRSDFile.h
  include/data/QSimRSDFileManager.h
  include/data/QSimRSDFileSerializer.h
  include/data/QSimSerializer.h
  include/data/QSimTexCodec.h
  include/data/QSimTexFile.h
  include/data/QSimTriggersFile.h
  include/data/QSimMapListFile.h
)

set(SOURCE_FILES_DATA
  src/common/QSimApplication.cpp
  src/data/QSimAFile.cpp
  src/data/QSimAFileManager.cpp
  src/data/QSimAFileSerializer.cpp
  src/data/worldmap/MapFile.cpp
  src/data/worldmap/MapFileManager.cpp
  src/data/worldmap/MapFileSerializer.cpp
  src/data/worldmap/TxzFile.cpp
  src/data/worldmap/TxzFileManager.cpp
  src/data/worldmap/TxzFileSerializer.cpp
  src/data/QSimBackgroundFile.cpp
  src/data/QSimBackgroundFileManager.cpp
  src/data/QSimBackgroundFileSerializer.cpp
  src/data/QSimBackgroundTextureLoader.cpp
  src/data/QSimCameraMatrixFile.cpp
  src/data/QSimCameraMatrixFileManager.cpp
  src/data/QSimCameraMatrixFileSerializer.cpp
  src/data/QSimFLevelBackground2DLoader.cpp
  src/data/QSimFLevelFile.cpp
  src/data/QSimFLevelFileManager.cpp
  src/data/QSimFLevelFileSerializer.cpp
  src/data/QSimFLevelTextureLoader.cpp
  src/data/QSimHRCFile.cpp
  src/data/QSimHRCFileManager.cpp
  src/data/QSimHRCFileSerializer.cpp
  src/data/QSimHRCMeshLoader.cpp
  src/data/QSimHRCSkeletonLoader.cpp
  src/data/QSimLGPArchive.cpp
  src/data/QSimLGPArchiveFactory.cpp
  src/data/QSimLGPArchiveSerializer.cpp
  src/data/QSimLZSDataStream.cpp
  src/data/QSimLZSFLevelFile.cpp
  src/data/QSimLZSFLevelFileManager.cpp
  src/data/QSimPaletteFile.cpp
  src/data/QSimPaletteFileManager.cpp
  src/data/QSimPaletteFileSerializer.cpp
  src/data/QSimPFile.cpp
  src/data/QSimPFileManager.cpp
  src/data/QSimPFileSerializer.cpp
  src/data/QSimRSDFile.cpp
  src/data/QSimRSDFileManager.cpp
  src/data/QSimRSDFileSerializer.cpp
  src/data/QSimSerializer.cpp
  src/data/QSimTexCodec.cpp
  src/data/QSimTexFile.cpp
  src/data/QSimTriggersFile.cpp
  src/data/QSimMapListFile.cpp
)

set(SOURCE_FILES
  src/modules/worldmap/WorldMapModule.cpp

  src/common/QSimManualObject.cpp
  src/common/QSimResource.cpp
  src/common/QSimStringUtil.cpp
  src/common/TypeDefine.cpp
  src/common/LzsFile.cpp
  src/common/File.cpp
  src/common/FileSystem.cpp
  src/core/particles/emitters/ParticlePointEmitter.cpp
  src/core/particles/Particle.cpp
  src/core/particles/ParticleEmitter.cpp
  src/core/particles/ParticleEmitterDictionary.cpp
  src/core/particles/ParticleEmitterTranslator.cpp
  src/core/particles/ParticleRenderer.cpp
  src/core/particles/ParticleRendererTranslator.cpp
  src/core/particles/ParticleSystem.cpp
  src/core/particles/ParticleSystemFactory.cpp
  src/core/particles/ParticleSystemManager.cpp
  src/core/particles/ParticleSystemTranslator.cpp
  src/core/particles/ParticleSystemTranslatorManager.cpp
  src/core/particles/ParticleTechnique.cpp
  src/core/particles/ParticleTechniqueTranslator.cpp
  src/core/particles/ParticleVisual.cpp
  src/core/particles/renderer/ParticleEntityRenderer.cpp
  src/core/particles/renderer/ParticleEntityRendererDictionary.cpp
  src/core/Background2D.cpp
  src/core/Background2DAnimation.cpp
  src/core/CameraManager.cpp
  src/core/ConfigCmd.cpp
  src/core/ConfigCmdManager.cpp
  src/core/ConfigFile.cpp
  src/core/ConfigVar.cpp
  src/core/ConfigVarManager.cpp
  src/core/Console.cpp
  src/core/DebugDraw.cpp
  src/core/Entity.cpp
  src/core/EntityCollision.cpp
  src/core/EntityDirection.cpp
  src/core/EntityManager.cpp
  src/core/EntityModel.cpp
  src/core/EntityPoint.cpp
  src/core/EntityTrigger.cpp
  src/core/GameFrameListner.cpp
  src/core/InputManager.cpp
  src/core/ScriptManager.cpp
  src/core/Timer.cpp
  src/core/UiAnimation.cpp
  src/core/UiFont.cpp
  src/core/UiManager.cpp
  src/core/UiSprite.cpp
  src/core/UiTextArea.cpp
  src/core/UiWidget.cpp
  src/core/Utilites.cpp
  src/core/Walkmesh.cpp
  src/core/XmlBackground2DFile.cpp
  src/core/XmlFile.cpp
  src/core/XmlFontFile.cpp
  src/core/XmlFontsFile.cpp
  src/core/XmlMapFile.cpp
  src/core/XmlMapsFile.cpp
  src/core/XmlPrototypesFile.cpp
  src/core/XmlScreenFile.cpp
  src/core/XmlScreensFile.cpp
  src/core/XmlScriptsFile.cpp
  src/core/XmlTextFile.cpp
  src/core/XmlTextsFile.cpp
  src/core/DialogsManager.cpp
  src/core/TextManager.cpp
  src/map/QSimBackground2DFile.cpp
  src/map/QSimBackground2DFileManager.cpp
  src/map/QSimBackground2DFileXMLSerializer.cpp
  src/map/QSimMapFile.cpp
  src/map/QSimMapFileManager.cpp
  src/map/QSimMapFileXMLSerializer.cpp
  src/map/QSimWalkmeshFile.cpp
  src/map/QSimWalkmeshFileManager.cpp
  src/map/QSimWalkmeshFileXMLSerializer.cpp
  #src/viewer/ViewerModule.cpp
  src/QSimGameState.cpp
  src/data/QSimXMLSerializer.cpp
)
if(QSim_SOUND)
    set(HEADER_FILES
        ${HEADER_FILES}
        include/core/AudioManager.h
        include/core/XmlMusicsFile.h
    )
    set(SOURCE_FILES
        ${SOURCE_FILES}
        src/core/AudioManager.cpp
        src/core/XmlMusicsFile.cpp
    )
endif()

include_directories(
    ${QSim_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include

    # TODO: remove dependency on ff7 related code
    ${QSim_SOURCE_DIR}/SupportedGames/FinalFantasy7/include
    ${CMAKE_CURRENT_SOURCE_DIR}/SupportedGames/FinalFantasy7/include

)

#compiler options
if (MSVC)
else()
if(WIN32)
    add_definitions(
      -W
      -mthreads
      -fmessage-length=0
      -fexceptions
      -fident
    )

    #linker options
    add_definitions(
      -Wl,--enable-runtime-pseudo-reloc
      -Wl,--enable-auto-image-base
      -Wl,--add-stdcall-alias
    )
endif()
endif()

#defines
if(WIN32)
  #check usage and remove if uneccessary
  add_definitions(-DWIN32 -D__WIN32__ -D_WINDOWS)
endif()

add_library(QSimMain STATIC
  ${HEADER_FILES}
  ${SOURCE_FILES}
)

# Coverage uses more memory, combined with PCH can cause OOM/ICE
#if ($ENV{COVERAGE}!=1)
cotire(QSimMain)
#endif()
SET_PROPERTY(TARGET QSimMain PROPERTY FOLDER "q-sim")

add_library(q-sim-data STATIC
 ${HEADER_FILES_DATA}
 ${SOURCE_FILES_DATA}
 )
add_dependencies(q-sim-data configure_qsim_version)
# Coverage uses more memory, combined with PCH can cause OOM/ICE
if ($ENV{COVERAGE}!=1)
cotire(q-sim-data)
endif()
SET_PROPERTY(TARGET q-sim-data PROPERTY FOLDER "q-sim")


add_executable(q-sim
  src/Main.cpp
)
SET_PROPERTY(TARGET q-sim PROPERTY FOLDER "q-sim")
set(CPACK_PACKAGE_EXECUTABLES q-sim "q-sim")
set(CPACK_WIX_PROGRAM_MENU_FOLDER "QSim")

if (APPLE)
target_link_libraries(q-sim "-framework CoreFoundation -framework Cocoa -framework IOKit")
endif()

if( WIN32 AND NOT (CMAKE_BUILD_TYPE MATCHES "Debug") )
    set_target_properties( q-sim PROPERTIES WIN32_EXECUTABLE ON )
	if (MSVC)
        set_target_properties(q-sim PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
    endif()
endif()

target_link_libraries(QSimMain 
    ${QSim_LIBRARIES}
    LuaBind
	liblua
    TinyXml
    FinalFantasy7
)

target_link_libraries(q-sim 
	QSimMain
	${Boost_LIBRARIES}
    q-sim-data
)

target_link_libraries(q-sim-data
    QSimMain
)

if(WIN32 OR APPLE)
  install(TARGETS q-sim DESTINATION .)
else()
  install(TARGETS q-sim RUNTIME DESTINATION ./games)
endif()
