#include <raylib-cpp.hpp>
#include <vector>
#include "Components.hpp"
#include "Game.hpp"
#include "spells/CastDirection.hpp"

#pragma once

class Spell {

    public:

        int manaCost;
        Projectile projectile; // Projectile to be cast
        Texture2D projectileTexture; // Texture to represent the projectile
        Texture2D spellTexture; // Texture to represent the spell
        std::vector<CastDirection> castDirections; // Directions that need to be pressed to cast the spell
        bool cast_on_death; // Cast when the projectile dies, even if it didn't hit anything

        std::function<void(Game*, raylib::Vector2)> castFunction; // Function to cast the spell

};

std::vector<Spell> loadSpells(); // Load all, not from file but maybe at some point.