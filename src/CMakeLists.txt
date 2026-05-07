cmake_minimum_required(VERSION 3.16)
project(Minesweeper1v1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Grab all source files
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Exclude anything inside the build directory
# Escape special regex characters in the path (e.g. C++ contains +)
file(TO_CMAKE_PATH "${CMAKE_BINARY_DIR}" BUILD_DIR_NORMALIZED)
string(REGEX REPLACE "([][+.*()^$|?])" "\\\\\\1" BUILD_DIR_ESCAPED "${BUILD_DIR_NORMALIZED}")
list(FILTER SOURCES EXCLUDE REGEX "^${BUILD_DIR_ESCAPED}/.*")

add_executable(minesweeper ${SOURCES})

target_include_directories(minesweeper PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/core"
    "${CMAKE_CURRENT_SOURCE_DIR}/game"
    "${CMAKE_CURRENT_SOURCE_DIR}/net"
    "${CMAKE_CURRENT_SOURCE_DIR}/scenes"
)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System Network)
target_link_libraries(minesweeper
    PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Network
)