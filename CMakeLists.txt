cmake_minimum_required(VERSION 3.0)


# Создание статической библиотеки
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
add_library(Editor STATIC src/garuEditor.cpp)


# Укажите директорию с заголовочными файлами для статической библиотеки

target_include_directories(Editor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)


# Создание исполняемого файла

add_executable(garu src/garu.cpp)


# Связывание исполняемого файла с библиотекой

target_link_libraries(garu Editor)
