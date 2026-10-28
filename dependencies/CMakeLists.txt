include_directories(
    ${QSim_INCLUDE_DIRS}
	luabind
	luajit/src
	luabind/luabind
	luabind/luabind/detail
	SUDM
)

add_subdirectory(tinyxml)
add_subdirectory(luajit)

SET(SUDM_AS_LIB TRUE CACHE BOOL "Build only lib")
add_subdirectory(SUDM)

 aux_source_directory( luabind/luabind LuaBind_header_FILES )
 aux_source_directory( luabind/luabind/details LuaBind_header_details_FILES )		
 aux_source_directory( luabind/src LuaBind_src_FILES )		
 add_library(LuaBind STATIC ${LuaBind_src_FILES} ${LuaBind_header_FILES} ${LuaBind_header_details_FILES})
 
 
# Ogre::UTFString was removed from OGRE 1.12, keep the last version around
add_library(OgreUTFString STATIC utfstring/OgreUTFString.cpp utfstring/OgreUTFString.h)
target_include_directories(OgreUTFString PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/utfstring)
target_link_libraries(OgreUTFString PUBLIC OgreMain)
set_property(TARGET OgreUTFString PROPERTY FOLDER "3rdparty")
