cmake_minimum_required(VERSION 3.16)
project(Minesweeper1v1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(minesweeper test.cpp)

target_link_libraries(minesweeper
    SFML::Graphics
    SFML::Window
    SFML::System
)