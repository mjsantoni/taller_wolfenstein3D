cmake_minimum_required(VERSION 3.10)
project(wolfenstein3d_editor)

add_subdirectory("../include/common/yaml-cpp" [binary_dir])

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -pthread")

INCLUDE(FindPkgConfig)

find_package(Qt5Widgets)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR} ../include ${PROJECT_BINARY_DIR})

set(CMAKE_AUTOMOC on)
set(CMAKE_CXX_STANDARD 11)

qt5_wrap_ui(UIS_HEADERS
        ../ui/editor.ui
        ../ui/connect.ui
        ../ui/recents.ui
        )

file(GLOB EDITOR_SRC
        "*.cpp"
        "../common_src/map_parser.cpp"
        "../common_src/coordinate.cpp"
        "*/*.cpp"
        )

add_executable(wolfenstein3d-editor ${EDITOR_SRC} ${UIS_HEADERS})

TARGET_LINK_LIBRARIES(wolfenstein3d-editor yaml-cpp Qt5::Widgets)

install(DIRECTORY ../maps ../config DESTINATION ${CMAKE_SOURCE_DIR})
