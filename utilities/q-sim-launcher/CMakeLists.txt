find_package ( Qt4 REQUIRED )
include ( ${QT_USE_FILE} )
include_directories (
	${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
	${QT_QTCORE_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR} ${QT_QTCORE_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR}
	)
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
QT4_WRAP_UI(UIS ${q-sim-launcher_UIS})

set ( q-sim-launcher_MOCS
	src/mainwindow.h
	)
QT4_WRAP_CPP(MOCS ${q-sim-launcher_MOCS})

add_definitions(
    -DQSIM_ADD_MANAGERS
)
add_executable ( q-sim-launcher ${q-sim-launcher_SRCS} ${UIS} ${RSCS} ${TRS} ${MOCS} )

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


target_link_libraries ( q-sim-launcher  ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${LIBRARIES})

if(WIN32 OR APPLE)
  install(TARGETS q-sim-launcher DESTINATION . ) 
else()
  install(TARGETS q-sim-launcher RUNTIME DESTINATION bin ) 
endif()
