cmake_minimum_required(VERSION 3.10)
project(AnglersOdyssey)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS Graphics Window System Audio REQUIRED)  # Fixed component names

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
target_link_libraries(AnglersOdyssey 
    SFML::Graphics 
    SFML::Window 
    SFML::System 
    SFML::Audio  # Use imported targets
)
