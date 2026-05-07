cmake_minimum_required(VERSION 3.16)
project(Minesweeper1v1Root)
 
# Prevent in-source builds (keeps root directory clean)
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "In-source builds are not allowed. Use build.py instead.")
endif()
 
add_subdirectory(src)
add_subdirectory(server)
 