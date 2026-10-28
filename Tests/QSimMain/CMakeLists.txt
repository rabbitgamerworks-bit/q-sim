file(COPY misc DESTINATION .)

include_directories(
    ${QSim_INCLUDE_DIRS}
    ${QSimMain_SOURCE_DIR}/include
)

set(LIBRARIES
    ${QSim_TEST_LIBRARIES}
    QSimMain
	q-sim-data
)

add_executable(TestQSimAFileSerializer
    src/test_QSimAFileSerializer.cpp
)
SET_PROPERTY(TARGET TestQSimAFileSerializer PROPERTY FOLDER "tests")

target_link_libraries(TestQSimAFileSerializer ${LIBRARIES})
add_test(NAME TestQSimAFileSerializer COMMAND TestQSimAFileSerializer)


add_executable(TestQSimMapFileXMLSerializer
    src/test_QSimMapFileXMLSerializer.cpp
)
SET_PROPERTY(TARGET TestQSimMapFileXMLSerializer PROPERTY FOLDER "tests")

target_link_libraries(TestQSimMapFileXMLSerializer ${LIBRARIES})
add_test(NAME TestQSimMapFileXMLSerializer COMMAND TestQSimMapFileXMLSerializer)

# field walk mesh
add_executable(TestQSimWalkmeshFileXMLSerializer
    src/test_QSimWalkmeshFileXMLSerializer.cpp
)
SET_PROPERTY(TARGET TestQSimWalkmeshFileXMLSerializer PROPERTY FOLDER "tests")

target_link_libraries(TestQSimWalkmeshFileXMLSerializer ${LIBRARIES})
add_test(NAME TestQSimWalkmeshFileXMLSerializer COMMAND TestQSimWalkmeshFileXMLSerializer)

# LGP archive
add_executable(TestQSimLGPArchive
    src/test_QSimLGPArchive.cpp
)
SET_PROPERTY(TARGET TestQSimLGPArchive PROPERTY FOLDER "tests")

target_link_libraries(TestQSimLGPArchive ${LIBRARIES})
add_test(NAME TestQSimLGPArchive COMMAND TestQSimLGPArchive)

# HRC archive
add_executable(TestQSimHRCSerializer
    src/test_QSimHRCSerializer.cpp
)
SET_PROPERTY(TARGET TestQSimHRCSerializer PROPERTY FOLDER "tests")

target_link_libraries(TestQSimHRCSerializer ${LIBRARIES})
add_test(NAME TestQSimHRCSerializer COMMAND TestQSimHRCSerializer)

# world map
add_executable(TestMapSerializer
    src/test_MapSerializer.cpp
)
SET_PROPERTY(TARGET TestMapSerializer PROPERTY FOLDER "tests")

target_link_libraries(TestMapSerializer ${LIBRARIES})
# TODO FIX ME - test not currently working
#add_test(TestMapSerializer TestMapSerializer)


add_executable(TestTxzSerializer
    src/test_TxzSerializer.cpp
)
SET_PROPERTY(TARGET TestTxzSerializer PROPERTY FOLDER "tests")


target_link_libraries(TestTxzSerializer ${LIBRARIES})
# TODO FIX ME - test not currently working
#add_test(TestTxzSerializer TestTxzSerializer)

