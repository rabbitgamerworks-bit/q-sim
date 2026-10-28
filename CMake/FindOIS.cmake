# Find the OIS (Object Oriented Input System) library.
#
# Provides the imported target OIS::OIS and the variables
#   OIS_FOUND, OIS_INCLUDE_DIRS, OIS_LIBRARIES
#
# Hints: OIS_HOME / OIS_ROOT (CMake or environment variables).

find_package(PkgConfig QUIET)
if(PKG_CONFIG_FOUND)
  pkg_check_modules(PC_OIS QUIET OIS)
endif()

find_path(OIS_INCLUDE_DIR OIS.h
  HINTS ${OIS_HOME} $ENV{OIS_HOME} ${OIS_ROOT} $ENV{OIS_ROOT} ${PC_OIS_INCLUDE_DIRS}
  PATH_SUFFIXES include include/OIS include/ois OIS ois
)

find_library(OIS_LIBRARY_RELEASE NAMES OIS
  HINTS ${OIS_HOME} $ENV{OIS_HOME} ${OIS_ROOT} $ENV{OIS_ROOT} ${PC_OIS_LIBRARY_DIRS}
  PATH_SUFFIXES lib lib/release lib/Release
)
find_library(OIS_LIBRARY_DEBUG NAMES OIS_d
  HINTS ${OIS_HOME} $ENV{OIS_HOME} ${OIS_ROOT} $ENV{OIS_ROOT} ${PC_OIS_LIBRARY_DIRS}
  PATH_SUFFIXES lib lib/debug lib/Debug
)

include(SelectLibraryConfigurations)
select_library_configurations(OIS)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(OIS
  REQUIRED_VARS OIS_LIBRARY OIS_INCLUDE_DIR
  VERSION_VAR PC_OIS_VERSION
)

if(OIS_FOUND)
  set(OIS_INCLUDE_DIRS ${OIS_INCLUDE_DIR})
  set(OIS_LIBRARIES ${OIS_LIBRARY})
  if(NOT TARGET OIS::OIS)
    add_library(OIS::OIS UNKNOWN IMPORTED)
    set_target_properties(OIS::OIS PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${OIS_INCLUDE_DIR}"
      IMPORTED_LOCATION "${OIS_LIBRARY_RELEASE}"
    )
    if(OIS_LIBRARY_DEBUG)
      set_target_properties(OIS::OIS PROPERTIES IMPORTED_LOCATION_DEBUG "${OIS_LIBRARY_DEBUG}")
    endif()
  endif()
endif()

mark_as_advanced(OIS_INCLUDE_DIR OIS_LIBRARY_RELEASE OIS_LIBRARY_DEBUG)
