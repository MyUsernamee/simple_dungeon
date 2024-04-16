# Simple Raylib project

cmake_minimum_required(VERSION 3.23)
project(raylib_project)

find_package(raylib 5.0 REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE dependencies/raylib-cpp/include)
target_include_directories(${PROJECT_NAME} PRIVATE src) # No include directory today lmao.

target_link_libraries(${PROJECT_NAME} raylib)