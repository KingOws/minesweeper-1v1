cmake_minimum_required(VERSION 3.16)
project(Minesweeper1v1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Grab all your files
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# 2. Create the executable
add_executable(minesweeper ${SOURCES})

# 3. FORCE the include paths (Hardcoded)
target_include_directories(minesweeper PRIVATE 
    "src"
    "src/core"
    "src/game"
    "src/net"
    "src/scenes"
    "C:/SFML-3.0.2/include"
)

# 4. Manually find the libraries (Hardcoded for MinGW)
target_link_libraries(minesweeper PRIVATE
    "C:/SFML-3.0.2/lib/libsfml-graphics.a"
    "C:/SFML-3.0.2/lib/libsfml-window.a"
    "C:/SFML-3.0.2/lib/libsfml-system.a"
    "C:/SFML-3.0.2/lib/libsfml-network.a"
)