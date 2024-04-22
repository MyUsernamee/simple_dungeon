#include <raylib-cpp.hpp>
#include <vector>
#include <Components.hpp>

#pragma once

/**
 * @brief Represents a direction that is needed to be pressed to cast a spell.
*/
enum class CastDirection {
    Up,
    Down,
    Left,
    Right
};

class Spell {

    public:

        int manaCost;
        Projectile projectile; // Projectile to be cast
        Texture2D projectileTexture; // Texture to represent the projectile
        Texture2D spellTexture; // Texture to represent the spell
        std::vector<CastDirection> castDirections; // Directions that need to be pressed to cast the spell
        bool cast_on_death; // Cast when the projectile dies, even if it didn't hit anything

        virtual void cast(raylib::Vector2 position, raylib::Vector2 direction) = 0; // When the projectile hits something or the lifetime is over


};