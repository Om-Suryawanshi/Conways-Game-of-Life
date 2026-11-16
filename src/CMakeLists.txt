add_library(game display.c)

target_include_directories(game PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)