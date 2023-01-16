cmake_minimum_required(VERSION 3.20)

project(ced3dsplit)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
add_definitions("/02")
else (WIN32)
add_definitions("-O3")
endif(WIN32)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(main main.cpp)
target_link_libraries(main ${CONAN_LIBS} i3dcore i3dalgo)
