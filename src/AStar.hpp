#include <vector>
#include <raylib-cpp.hpp>

#pragma once


std::vector<raylib::Vector2> findPath(raylib::Vector2 start, raylib::Vector2 end, int* map, int mapWidth, int mapHeight);