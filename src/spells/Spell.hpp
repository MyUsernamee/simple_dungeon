#include <raylib-cpp.hpp>
#include <vector>
#include "../Components.hpp"

#pragma once

class Game; // Forward declaration

class Spell {

    public:

        // Cost of the spell
        int manaCost = 1;
        double castDelay = 0.0; // Time it takes for the spell to cast
        double castCooldown = 0.0; // Timer used for the cooldown of the spell

        // Casts the spell in the given direction.
        virtual void cast(Game* game, entt::entity entity, raylib::Vector2 direction) = 0;

        // TODO: Add other vital data like the name and basic texture that represents the spell.

};

void loadSpells(Game* game); // Load the spells into the game