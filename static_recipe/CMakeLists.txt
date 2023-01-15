cmake_minimum_required(VERSION 3.20)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 20)

project(ced3dsplit)

# For location i3dlib
if(WIN32)
  include_directories(${CMAKE_BINARY_DIR}/include)
  link_directories(${CMAKE_BINARY_DIR}/lib)
endif(WIN32)

add_executable(ced_3d_splitted ../main.cpp)

# I3D deps ===================

find_package(FFTW3 CONFIG REQUIRED)
set(LIBS ${LIBS} FFTW3::fftw3)

find_package(FFTW3f CONFIG REQUIRED)
set(LIBS ${LIBS} FFTW3::fftw3f)

find_package(FFTW3l CONFIG REQUIRED)
set(LIBS ${LIBS} FFTW3::fftw3l)

find_package(clapack CONFIG REQUIRED)
set(LIBS ${LIBS} lapack)

if(UNIX)
  if(NOT APPLE)
    set(LIBS ${LIBS} f2c)
  endif(NOT APPLE)
endif(UNIX)

find_package(OpenBLAS CONFIG REQUIRED)
set(LIBS ${LIBS} OpenBLAS::OpenBLAS)

find_package(TIFF REQUIRED)
set(LIBS ${LIBS} ${TIFF_LIBRARIES})

find_package(JPEG REQUIRED)
set(LIBS ${LIBS} ${JPEG_LIBRARIES})

find_package(libpng CONFIG REQUIRED)
if(WIN32)
  set(LIBS ${LIBS} png)
else(WIN32)
  set(LIBS ${LIBS} png_static)
endif(WIN32)

find_package(libics CONFIG REQUIRED)
set(LIBS ${LIBS} libics)

find_package(ZLIB REQUIRED)
set(LIBS ${LIBS} ZLIB::ZLIB)

find_package(hdf5 CONFIG REQUIRED)
if(WIN32)
  set(LIBS ${LIBS} hdf5::hdf5-shared hdf5::hdf5_hl-shared)
else(WIN32)
  set(LIBS ${LIBS} hdf5::hdf5-static hdf5::hdf5_hl-static)
endif(WIN32)

find_package(RXSpencer CONFIG REQUIRED)
set(LIBS ${LIBS} rxspencer)

find_package(Boost REQUIRED program_options)
set(LIBS ${LIBS} Boost::boost Boost::program_options)

find_package(fmt CONFIG REQUIRED)
set(LIBS ${LIBS} fmt::fmt)


set(CMAKE_FIND_LIBRARY_SUFFIXES .a .lib)
find_library(I3DCORE i3dcore)
find_library(I3DALGO i3dalgo)

message("Found i3dcore: ${I3DCORE}")
message("Found i3dalgo: ${I3DALGO}")

target_link_libraries(ced_3d_splitted ${I3DALGO} ${I3DCORE} ${LIBS})
