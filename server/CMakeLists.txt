cmake_minimum_required(VERSION 3.16)
project(Minesweeper1v1Server)
 
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
 
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
 
# Exclude build directory (escaping special chars like + in path)
file(TO_CMAKE_PATH "${CMAKE_BINARY_DIR}" BUILD_DIR_NORMALIZED)
string(REGEX REPLACE "([][+.*()^$|?])" "\\\\\\1" BUILD_DIR_ESCAPED "${BUILD_DIR_NORMALIZED}")
list(FILTER SOURCES EXCLUDE REGEX "^${BUILD_DIR_ESCAPED}/.*")
 
add_executable(minesweeper_server ${SOURCES})
 
target_compile_features(minesweeper_server PRIVATE cxx_std_20)
 
find_package(SFML 3 REQUIRED COMPONENTS Network System)
target_link_libraries(minesweeper_server
    PRIVATE
    SFML::Network
    SFML::System
)