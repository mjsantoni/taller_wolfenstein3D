cmake_minimum_required(VERSION 3.17)
project(tp_wolfenstein)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
SET(CMAKE_CXX_FLAGS -pthread)

INCLUDE(FindPkgConfig)

find_package(yaml-cpp REQUIRED)
find_package(Qt5Widgets)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_check_modules(SDL2_Mixer REQUIRED IMPORTED_TARGET SDL2_mixer)


INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include ${PROJECT_BINARY_DIR} ${YAML_INCLUDE_DIRS})
set(CMAKE_AUTOMOC on)

set(CMAKE_CXX_STANDARD 11)

file(GLOB All_SRC
        "server_src/server_main.cpp"
        "editor_src/*.cpp"
        "server_src/*.cpp"
        "server_src/*/*.cpp"
        "client_src/*.cpp"
        "common_src/*.cpp"
        "server_src/*/*.cpp"
        )

file(GLOB CLIENT_SRC
        "client_src/*/*.cpp"
        "client_src/*.cpp"
        "common_src/*.cpp"
        )

file(GLOB SERVER_SRC
        "server_src/*.cpp"
        "server_src/*/*.cpp"
        )

file(GLOB EDITOR_SRC
        "editor_src/*.cpp"
        "server_src/game/map_parser.cpp"
        "editor_src/*/*.cpp"
        )

qt5_wrap_ui(UIS_HEADERS
        ui/editor.ui
        )

add_executable(tp_wolfenstein ${All_SRC} ${UIS_HEADERS})
add_executable(server ${SERVER_SRC})
add_executable(client ${CLIENT_SRC})
add_executable(editor ${EDITOR_SRC} ${UIS_HEADERS})


TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} PkgConfig::SDL2_Mixer ${YAML_CPP_LIBRARIES} Qt5::Widgets)
TARGET_LINK_LIBRARIES(server ${YAML_CPP_LIBRARIES})
TARGET_LINK_LIBRARIES(editor ${YAML_CPP_LIBRARIES} Qt5::Widgets)
TARGET_LINK_LIBRARIES(client ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} PkgConfig::SDL2_Mixer)