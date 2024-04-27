# Simple Raylib project

cmake_minimum_required(VERSION 3.23)
project(raylib_project)

# Use Cxx11_string abi
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLIBCXX_USE_CXX11_ABI=0")


# On build copy the assets folder to the build directory
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

find_package(raylib 5.0 REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

include_directories(src) # No include directory today lmao.
include_directories(dependencies/raygui/src)
include_directories(dependencies/raylib-cpp/include)
include_directories(dependencies/entt/src) # Header only library ECS :)
include_directories(dependencies/wfc-cpp/src) # Header only library WFC :)
include_directories(dependencies/delaunator-cpp/include) # Header only library Delaunator :)
include_directories(dependencies/cereal/include) # Header only library Serialization :)
include_directories(dependencies/json/include) # Header only library Serialization :)

# Set it so Wfatal-errors is on by default
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wfatal-errors")

add_executable(${PROJECT_NAME} ${SOURCES})

# Remove the main.cpp
list(REMOVE_ITEM SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
# Add a tileset tool 
#add_executable(tileset_tool ${SOURCES} tools/tileset_tool.cpp)
add_executable(particle_designer ${SOURCES} tools/particle_designer.cpp)
add_executable(tileset_maker ${SOURCES} tools/tileset_maker.cpp)
add_executable(test_dungeon_generator ${SOURCES} tools/test_dungeon_generator.cpp)

target_link_libraries(${PROJECT_NAME} raylib)
#target_link_libraries(tileset_tool raylib)
target_link_libraries(particle_designer raylib)
target_link_libraries(tileset_maker raylib)
target_link_libraries(test_dungeon_generator raylib)