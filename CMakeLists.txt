cmake_minimum_required(VERSION 3.22)
project(counter)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(Google_tests)

add_executable(counter main.cpp
        src/InputController.cpp
        src/GameController.cpp
        src/Player.cpp
        src/Weapon.cpp
        src/OutputController.cpp)

target_include_directories(counter PRIVATE src/)
