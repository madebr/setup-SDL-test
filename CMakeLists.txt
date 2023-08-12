cmake_minimum_required(VERSION 3.16)
project(setup_sdl_test)

find_package(SDL3 REQUIRED COMPONENTS SDL3 SDL3_test)

add_executable(main main.c)
target_link_libraries(main PRIVATE SDL3::SDL3_test SDL3::SDL3)
