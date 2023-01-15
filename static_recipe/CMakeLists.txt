cmake_minimum_required(VERSION 3.20)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 20)

project(ced3dsplit)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# For location i3dlib
if(WIN32)
  include_directories(${CMAKE_BINARY_DIR}/include)
  link_directories(${CMAKE_BINARY_DIR}/lib)
endif(WIN32)

add_executable(ced_3d_splitted ../main.cpp)

find_package(clapack CONFIG REQUIRED)
set(VCPKG_LIBS ${VCPKG_LIBS} f2c lapack)

find_package(libics CONFIG REQUIRED)
set(VCPKG_LIBS ${VCPKG_LIBS} libics)

find_package(RXSpencer CONFIG REQUIRED)
set(VCPKG_LIBS ${VCPKG_LIBS} rxspencer)

set(CMAKE_FIND_LIBRARY_SUFFIXES .a .lib)
find_library(I3DCORE i3dcore)
find_library(I3DALGO i3dalgo)

message("Found i3dcore: ${I3DCORE}")
message("Found i3dalgo: ${I3DALGO}")

target_link_libraries(ced_3d_splitted ${I3DALGO} ${I3DCORE} ${VCPKG_LIBS}
                      ${CONAN_LIBS})
