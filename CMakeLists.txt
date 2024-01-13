cmake_minimum_required(VERSION 3.16)
project(setup_sdl_test)

find_package(SDL3 REQUIRED COMPONENTS SDL3 SDL3_test)
find_package(SDL3_image REQUIRED)
find_package(SDL3_mixer REQUIRED)
find_package(SDL3_ttf REQUIRED)
find_package(SDL3_rtf REQUIRED)
find_package(SDL3_net REQUIRED)

add_executable(main main.c)
target_link_libraries(main PRIVATE SDL3::SDL3_test SDL3::SDL3)
