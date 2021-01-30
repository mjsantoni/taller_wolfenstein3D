project(hello)
add_executable(hello test.cpp)
target_link_libraries(hello lua5.3)
