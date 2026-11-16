cmake_minimum_required(VERSION 3.10)

project(Conways_Game_Of_Life
    LANGUAGES C
    VERSION 1.0
)

add_subdirectory(src)

add_executable(CGOL main.c)

target_include_directories(CGOL PRIVATE ${CMAKE_SOURCE_DIR}/src/include)

target_link_libraries(CGOL PRIVATE game)