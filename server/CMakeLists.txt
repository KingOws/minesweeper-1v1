cmake_minimum_required(VERSION 3.16)
project(Minesweeper1v1Server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(Minesweeper main.cpp gameserver.cpp game.cpp player.cpp)

target_compile_features(Minesweeper PRIVATE cxx_std_20)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System Network)
target_link_libraries(Minesweeper
    PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Network
)