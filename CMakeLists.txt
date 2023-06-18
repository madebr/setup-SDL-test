cmake_minimum_required(VERSION 3.0.0)
project(setup-SDL VERSION 0.1.0 LANGUAGES C)

add_executable(setup-SDL main.c)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(setup-SDL PRIVATE SDL2::SDL2main SDL2::SDL2)
