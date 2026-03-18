cmake_minimum_required(VERSION 3.16)

project(Minesweeper1v1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(minesweeper
    driver.cpp
    board.cpp
    player.cpp
    tile.cpp
    menu.cpp
    spritemanager.cpp
)

target_link_libraries(minesweeper
    PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)