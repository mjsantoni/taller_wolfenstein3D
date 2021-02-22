cmake_minimum_required(VERSION 3.10)
project(wolfenstein3d_client)

add_subdirectory("../include/common/yaml-cpp" [binary_dir])

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -pthread")

INCLUDE(FindPkgConfig)

find_package(Qt5Widgets)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_check_modules(SDL2_Mixer REQUIRED IMPORTED_TARGET SDL2_mixer)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR} ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ../include ${PROJECT_BINARY_DIR})

set(CMAKE_CXX_STANDARD 11)

qt5_wrap_ui(UIS_HEADERS
        ../ui/editor.ui
        ../ui/connect.ui)

file(GLOB CLIENT_SRC
        "*/*.cpp"
        "*.cpp"
        "../common_src/*.cpp"
        )

add_executable(wolfenstein3d-client ${CLIENT_SRC} ${UIS_HEADERS})

TARGET_LINK_LIBRARIES(wolfenstein3d-client yaml-cpp ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} Qt5::Widgets PkgConfig::SDL2_Mixer)

install(DIRECTORY ../maps ../config DESTINATION ${CMAKE_SOURCE_DIR})