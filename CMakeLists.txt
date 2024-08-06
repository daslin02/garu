cmake_minimum_required(VERSION 3.0)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
add_library(Editor STATIC src/garuEditor.cpp)

target_include_directories(Editor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_executable(garu src/garu.cpp)

target_link_libraries(garu Editor)
