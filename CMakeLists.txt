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

set(CMAKE_CXX_STANDARD 11)

file(GLOB All_SRC
    "main.cpp"
    "client_src/game/*.cpp"
    "client_src/graphics/*.cpp"
    "client_src/music/*.cpp"
    "client_src/exceptions/*.cpp"
    "client_src/resources/*.cpp"
    "editor_src/*.cpp"
    "server_src/*.cpp"
    "server_src/game/*.cpp"
)

qt5_wrap_ui(UIS_HEADERS
        ui/editor.ui
        )
add_executable(tp_wolfenstein ${All_SRC} ${UIS_HEADERS})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} PkgConfig::SDL2_Mixer ${YAML_CPP_LIBRARIES} Qt5::Widgets)