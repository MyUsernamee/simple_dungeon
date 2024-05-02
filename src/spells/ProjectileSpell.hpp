
#pragma once
#include <entt/entt.hpp>
#include "spells/Spell.hpp"

class Game; // Forward declaration 

// Creates a projectile that moves in a straight line and performs an action when it hits an entity
class ProjectileSpell : public Spell {

    public:

        void cast(Game* game, entt::entity entity, CastDirection direction) override;
        // 
        void onHit(Game* game, entt::entity entity, entt::entity hitEntity);

}