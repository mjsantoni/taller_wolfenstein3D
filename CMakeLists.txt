cmake_minimum_required(VERSION 3.10)
project(tp_wolfenstein)

add_subdirectory("include/common/yaml-cpp")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

INCLUDE(FindPkgConfig)

find_package(Qt5Widgets)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_check_modules(SDL2_Mixer REQUIRED IMPORTED_TARGET SDL2_mixer)


INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include ${PROJECT_BINARY_DIR})
set(CMAKE_AUTOMOC on)
set(CMAKE_CXX_STANDARD 11)

file(GLOB CLIENT_SRC
        "client_src/*/*.cpp"
        "client_src/*.cpp"
        "common_src/*.cpp"
        )

file(GLOB SERVER_SRC
        "server_src/*.cpp"
        "server_src/*/*.cpp"
        "common_src/*.cpp"
        )

qt5_wrap_ui(UIS_HEADERS
        ui/editor.ui
        ui/connect.ui
        )

file(GLOB EDITOR_SRC
        "editor_src/*.cpp"
        "common_src/map_parser.cpp"
        "common_src/coordinate.cpp"
        "editor_src/*/*.cpp"
        )

add_executable(server ${SERVER_SRC})
add_executable(client ${CLIENT_SRC} ${UIS_HEADERS})
add_executable(editor ${EDITOR_SRC} ${UIS_HEADERS})


TARGET_LINK_LIBRARIES(server yaml-cpp lua5.3)
TARGET_LINK_LIBRARIES(editor yaml-cpp Qt5::Widgets)
TARGET_LINK_LIBRARIES(client yaml-cpp ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} Qt5::Widgets PkgConfig::SDL2_Mixer)