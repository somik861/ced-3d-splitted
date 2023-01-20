cmake_minimum_required(VERSION 3.20)

project(ced3dsplit)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
set(CORE_NAME cbia.lib.i3dcore.dyn.rel.x64.16)
set(ALGO_NAME cbia.lib.i3dalgo.dyn.rel.x64.16)
add_definitions("/O2")
link_directories("${CMAKE_SOURCE_DIR}/i3dlib_win/lib")
include_directories("${CMAKE_SOURCE_DIR}/i3dlib_win/include")
file(COPY "${CMAKE_SOURCE_DIR}/i3dlib_win/bin/${CORE_NAME}.dll" DESTINATION "${CMAKE_BINARY_DIR}/bin/")
file(COPY "${CMAKE_SOURCE_DIR}/i3dlib_win/bin/${ALGO_NAME}.dll" DESTINATION "${CMAKE_BINARY_DIR}/bin/")

set(I3D_LIBS "${CORE_NAME}.lib" "${ALGO_NAME}.lib")

else (WIN32)

add_definitions("-O3")
set(I3D_LIBS i3dcore i3dalgo)

endif(WIN32)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(ced3dsplit main.cpp)
target_link_libraries(ced3dsplit ${CONAN_LIBS} ${I3D_LIBS})
