#include <vector>
#include <raylib-cpp.hpp>
#include <functional>

#pragma once
namespace std {
    template <>
    struct hash<raylib::Vector2> {
        std::size_t operator()(const raylib::Vector2& k) const {
            // Compute individual hash values for two elements in the vector and combine them using XOR and bit shifting:
            return ((hash<float>()(k.x) ^ (hash<float>()(k.y) << 1)) >> 1);
        }
    };
}

double def_heuristic(raylib::Vector2 a, raylib::Vector2 b, int tile = 0);

std::vector<raylib::Vector2> findPath(raylib::Vector2 start, raylib::Vector2 end, int* map, int mapWidth, int mapHeight, std::function<double(raylib::Vector2, raylib::Vector2, int)> heuristic = &def_heuristic);