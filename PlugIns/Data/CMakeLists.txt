set(QSimMain_SOURCE_DIR ../../QSimMain)

# define header and source files for the library
set(HEADER_FILES
  ${QSimMain_SOURCE_DIR}/include/QSimPrerequisites.h
  ${QSimMain_SOURCE_DIR}/include/common/QSimManualObject.h
  ${QSimMain_SOURCE_DIR}/include/common/QSimStringUtil.h
  ${QSimMain_SOURCE_DIR}/include/common/TypeDefine.h
  include/QSimDataPlugin.h
)
set(SOURCE_FILES
  ${QSimMain_SOURCE_DIR}/src/common/QSimManualObject.cpp
  ${QSimMain_SOURCE_DIR}/src/common/QSimStringUtil.cpp
  ${QSimMain_SOURCE_DIR}/src/common/TypeDefine.cpp
  src/QSimDataPlugin.cpp
  src/QSimDataPluginDll.cpp
)

include_directories(
    ${OIS_INCLUDE_DIRS}
    ${OGRE_INCLUDE_DIRS}
    ${OGRE_SAMPLES_INCLUDEPATH}
    ${QSimMain_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../dependencies
)

#defines
#add_definitions(-DBOOST_ALL_DYN_LINK)

add_library(DataPlugin MODULE
  ${HEADER_FILES}
  ${SOURCE_FILES}
)
SET_PROPERTY(TARGET DataPlugin PROPERTY FOLDER "q-sim")

set_target_properties(DataPlugin PROPERTIES
  PREFIX ${PLUGIN_PREFIX}
  OUTPUT_NAME Data
)

set(LIBRARIES
  ${OGRE_LIBRARIES} 
  FinalFantasy7
  q-sim-data
)

target_link_libraries(DataPlugin ${LIBRARIES})

if(NOT QSIM_STATIC)
  set_target_properties(DataPlugin PROPERTIES
    COMPILE_DEFINITIONS QSIM_DATAPLUGIN_EXPORTS
  )
    if(WIN32 OR APPLE)
      install(TARGETS DataPlugin LIBRARY DESTINATION .)
    else()
      install(TARGETS DataPlugin LIBRARY DESTINATION ./lib/q-sim/plugins/ )
    endif()
endif()
