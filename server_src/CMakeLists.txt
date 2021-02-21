cmake_minimum_required(VERSION 3.10)
project(wolfenstein3d_server)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

INCLUDE(FindPkgConfig)

find_package(yaml-cpp REQUIRED)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR} ../include  ${YAML_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)

file(GLOB SERVER_SRC
        "*.cpp"
        "*/*.cpp"
        "../common_src/*.cpp"
        )

add_executable(server ${SERVER_SRC})

TARGET_LINK_LIBRARIES(server ${YAML_CPP_LIBRARIES} lua5.3)