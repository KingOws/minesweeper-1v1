cmake_minimum_required(VERSION 3.16)
project(Minesweeper1v1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 1. Grab all source files
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# 2. Create the executable
add_executable(minesweeper ${SOURCES})

# 3. Include paths — missing PUBLIC/PRIVATE keyword
target_include_directories(minesweeper PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/core"
    "${CMAKE_CURRENT_SOURCE_DIR}/game"
    "${CMAKE_CURRENT_SOURCE_DIR}/net"
    "${CMAKE_CURRENT_SOURCE_DIR}/scenes"
)

# 4. Find and link SFML
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System Network)
target_link_libraries(minesweeper
    PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Network
)