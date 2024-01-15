cmake_minimum_required(VERSION 3.20)
project(setup_sdl_test)

option(SDLNET_AVAIlABLE "Is SDL_net available?" ON)

find_package(SDL2 REQUIRED COMPONENTS SDL2 SDL2test)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_rtf REQUIRED)
if(SDLNET_AVAIlABLE)
    find_package(SDL2_net REQUIRED)
endif()

add_executable(main main.c)
if(SDLNET_AVAIlABLE)
    target_link_libraries(main PRIVATE SDL2_net::SDL2_net)
endif()
target_compile_definitions(main PRIVATE $<$<BOOL:${SDLNET_AVAIlABLE}>:WITH_SDLNET>)
target_link_libraries(main PRIVATE
    SDL2_image::SDL2_image
    SDL2_mixer::SDL2_mixer
    SDL2_rtf::SDL2_rtf
    SDL2_ttf::SDL2_ttf
    SDL2::SDL2test
    SDL2::SDL2main
    SDL2::SDL2
)
