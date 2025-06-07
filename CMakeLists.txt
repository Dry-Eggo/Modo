cmake_minimum_required(VERSION 3.12)
project(modo)


file(GLOB SRC src/main.cpp)
add_executable(modo ${SRC})
target_link_libraries(modo PUBLIC ncurses)
