#include <raylib-cpp.hpp>
#include <vector>
#include "../Components.hpp"
#include "spells/CastDirection.hpp"

#pragma once

class Game; // Forward declaration

class Spell {

    public:

        // Cost of the spell
        int manaCost;

        // Casts the spell in the given direction.
        virtual void cast(Game* game, entt::entity entity, CastDirection direction) = 0;

        // TODO: Add other vital data like the name and basic texture that represents the spell.

};

std::vector<Spell> loadSpells();