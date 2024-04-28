/*

    This folder and file contains all utility functions / classes used in the game.

    If a class / function doesn't directly relate to the game, it should be placed here.

    For example: TileSet and Animation classes are not directly contributing to gamelogic, so they are placed here.
    While the Dungeon class is directly related to the game, so it is placed in the src folder.

*/

#include <raylib-cpp.hpp>
#include <entt/entt.hpp>
#include <limits>

#include <cereal/cereal.hpp>

#pragma once

double GetRandomValue(double min, double max);

template <typename Archive>
void serialize(Archive &archive, raylib::Vector2& vector) {
    archive(CEREAL_NVP(vector.x), CEREAL_NVP(vector.y));
}

int operator<(const raylib::Vector2& lhs, const raylib::Vector2& rhs);