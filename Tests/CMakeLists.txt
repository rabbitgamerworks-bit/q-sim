add_definitions(
    -DBOOST_TEST_MODULE="standalone"
)

if(UNIX OR APPLE)
    add_definitions(
        -DBOOST_TEST_DYN_LINK
    )
endif()

set(QSimMain_SOURCE_DIR ${QSim_SOURCE_DIR}/QSimMain)

add_subdirectory(QSimMain)
add_subdirectory(FinalFantasy7)
