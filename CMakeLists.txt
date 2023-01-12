cmake_minimum_required(VERSION 3.20)

project(ced2dsplit)

set(CMAKE_CXX_STANDARD 20)
add_definitions("-O3 -flto=5")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(main main.cpp)
target_link_libraries(main ${CONAN_LIBS})
