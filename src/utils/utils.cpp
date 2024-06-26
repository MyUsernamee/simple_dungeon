/*

    This folder and file contains all utility functions / classes used in the game.

    If a class / function doesn't directly relate to the game, it should be placed here.

    For example: TileSet and Animation classes are not directly contributing to gamelogic, so they are placed here.
    While the Dungeon class is directly related to the game, so it is placed in the src folder.

*/

#include "utils.hpp"
#include <cereal/cereal.hpp>

double GetRandomValue(double min, double max) {
    return min + (static_cast<float>(GetRandomValue(0, std::numeric_limits<int>::max())) / static_cast<float>(std::numeric_limits<int>::max())) * (max - min);
}

int operator<(const raylib::Vector2& lhs, const raylib::Vector2& rhs) {
    if (lhs.x < rhs.x) {
        return true;
    } else if (lhs.x == rhs.x) {
        return lhs.y < rhs.y;
    } else {
        return false;
    }
}