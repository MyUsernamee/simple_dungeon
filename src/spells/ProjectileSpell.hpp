
#pragma once
#include <entt/entt.hpp>
#include "spells/Spell.hpp"
#include "Components.hpp"

class Game; // Forward declaration 

// Creates a projectile that moves in a straight line and performs an action when it hits an entity
class ProjectileSpell : public Spell {

    public:

        double projectileSpeed = 10.0;
        double projectileSize = 8.0;
        double projectileLifetime = 5.0;
        double projectileDamage = 1.0;


        void cast(Game* game, entt::entity entity, raylib::Vector2 direction) override;
        virtual void onHit(Game* game, entt::entity entity, entt::entity hitEntity) = 0;

};

class SimpleDamageSpell : public ProjectileSpell {

    public:

        void onHit(Game* game, entt::entity entity, entt::entity hitEntity) override {}; // Do nothing

};