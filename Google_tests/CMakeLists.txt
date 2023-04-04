project(Google_tests)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

add_executable(Google_Tests_run
        GamecontrollerTEST.cpp
        InputControllerTEST.cpp
        OutputControllerTEST.cpp
        PlayerTEST.cpp
        WeaponTEST.cpp
        ../src/GameController.cpp
        ../src/Player.cpp
        ../src/Weapon.cpp
        ../src/InputController.cpp)

target_include_directories(Google_Tests_run PRIVATE ../src/)

target_link_libraries(Google_Tests_run gtest gmock_main)