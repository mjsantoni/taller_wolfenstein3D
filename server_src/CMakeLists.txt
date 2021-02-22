cmake_minimum_required(VERSION 3.10)
project(wolfenstein3d_server)

add_subdirectory("../include/common/yaml-cpp" [binary_dir])

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

INCLUDE(FindPkgConfig)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR} ../include ${PROJECT_BINARY_DIR})

set(CMAKE_CXX_STANDARD 11)

file(GLOB SERVER_SRC
        "*.cpp"
        "*/*.cpp"
        "../common_src/*.cpp"
        )

add_executable(wolfenstein3d-server ${SERVER_SRC})

TARGET_LINK_LIBRARIES(wolfenstein3d-server yaml-cpp lua5.3)

install(DIRECTORY ../maps ../config DESTINATION ${CMAKE_SOURCE_DIR})