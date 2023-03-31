cmake_minimum_required(VERSION 3.22)
project(counter)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(Google_tests)
add_executable(counter main.cpp src/InputController.cpp src/InputController.h src/GameController.cpp src/GameController.h src/Player.cpp src/Player.h src/Weapon.cpp src/Weapon.h src/OutputController.cpp src/OutputController.h )
