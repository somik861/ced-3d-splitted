cmake_minimum_required(VERSION 3.20)

project(ced3dsplit)

set(CMAKE_CXX_STANDARD 20)
add_definitions("-O3 -flto=3")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(ced_3d_splitted ../main.cpp)


find_package(clapack CONFIG REQUIRED)
set(VCPKG_LIBS ${VCPKG_LIBS} f2c lapack)

find_package(libics CONFIG REQUIRED)
set(VCPKG_LIBS ${VCPKG_LIBS} libics)

find_package(RXSpencer CONFIG REQUIRED)
set(VCPKG_LIBS ${VCPKG_LIBS} rxspencer)

target_link_libraries(ced_3d_splitted ${VCPKG_LIBS} ${CONAN_LIBS} libi3dcore.a libi3dalgo.a)
