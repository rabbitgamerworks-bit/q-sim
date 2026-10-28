find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
message(STATUS "q-sim-launcher: using Qt ${QT_VERSION}")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set ( q-sim-launcher_HDRS
	src/mainwindow.h
	src/ff7DataInstaller.h
    src/ff7FieldTextWriter.h
	)

set ( q-sim-launcher_SRCS
	src/main.cpp
	src/mainwindow.cpp
	src/ff7DataInstaller.cpp
    src/ff7FieldTextWriter.cpp
	)

set ( q-sim-launcher_UIS
	src/mainwindow.ui
	)

add_definitions(
    -DQSIM_ADD_MANAGERS
)
add_executable ( q-sim-launcher ${q-sim-launcher_SRCS} ${q-sim-launcher_HDRS} ${q-sim-launcher_UIS} )

SET_PROPERTY(TARGET q-sim-launcher PROPERTY FOLDER "utilities")

if (APPLE)
target_link_libraries(q-sim-launcher "-framework CoreFoundation -framework Cocoa -framework IOKit")
endif()

if(WIN32)
  set_target_properties(q-sim-launcher PROPERTIES WIN32_EXECUTABLE ON)
  if (MSVC)
    set_target_properties(q-sim-launcher PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
  endif()
endif()

set(LIBRARIES
    Utility
    QSimMain
    q-sim-data
    Sudm_Lib
)


target_link_libraries ( q-sim-launcher Qt${QT_VERSION_MAJOR}::Widgets ${LIBRARIES})

if(WIN32 OR APPLE)
  install(TARGETS q-sim-launcher DESTINATION . ) 
else()
  install(TARGETS q-sim-launcher RUNTIME DESTINATION bin ) 
endif()
