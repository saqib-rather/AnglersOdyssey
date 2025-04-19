cmake_minimum_required(VERSION 3.10)
project(AnglersOdyssey)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

add_executable(AnglersOdyssey
    src/main.cpp
    src/Game.cpp
    src/Player.cpp
    src/Fish.cpp
    src/Hook.cpp
    src/UI.cpp
    src/Menu.cpp
    src/ParticleSystem.cpp
)

target_include_directories(AnglersOdyssey PRIVATE include)
target_link_libraries(AnglersOdyssey sfml-graphics sfml-window sfml-system sfml-audio)
