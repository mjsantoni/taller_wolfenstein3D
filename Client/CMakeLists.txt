cmake_minimum_required(VERSION 3.17)
project(tp_wolfenstein)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
SET(CMAKE_CXX_FLAGS -pthread)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_check_modules(SDL2_Mixer REQUIRED IMPORTED_TARGET SDL2_mixer)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)

file(GLOB Client_SRC
    "main.cpp"
    "Game/*.cpp"
    "Game/*.h"
    "Graphics/*.cpp"
    "Graphics/*.h"
    "Exceptions/*.cpp"
    "Exceptions/*.h"
    "Music/*.cpp"
    "Music/*.h"
    "Resources/*.cpp"
    "Resources/*.h"
)

add_executable(tp_wolfenstein ${Client_SRC})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} PkgConfig::SDL2_Mixer)