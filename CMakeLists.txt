cmake_minimum_required(VERSION 3.16)
project(setup_sdl_test)

option(SDLNET_AVAIlABLE "Is SDL_net available?" ON)

find_package(SDL3 REQUIRED COMPONENTS SDL3 SDL3_test)
find_package(SDL3_image REQUIRED)
find_package(SDL3_mixer REQUIRED)
find_package(SDL3_ttf REQUIRED)
find_package(SDL3_rtf REQUIRED)
if(SDLNET_AVAIlABLE)
    find_package(SDL3_net REQUIRED)
endif()

add_executable(main main.c)
if(SDLNET_AVAIlABLE)
    target_link_libraries(main PRIVATE SDL3_net::SDL3_net)
endif()
target_link_libraries(main PRIVATE
    SDL3_image::SDL3_image
    SDL3_mixer::SDL3_mixer
    SDL3_rtf::SDL3_rtf
    SDL3_ttf::SDL3_ttf
    SDL3::SDL3_test
    SDL3::SDL3
)
