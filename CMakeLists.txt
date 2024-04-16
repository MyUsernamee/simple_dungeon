# Simple Raylib project

cmake_minimum_required(VERSION 3.23)
project(raylib_project)

# On build copy the assets folder to the build directory
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

find_package(raylib 5.0 REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

include_directories(src) # No include directory today lmao.
include_directories(dependencies/raylib-cpp/include)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} raylib)