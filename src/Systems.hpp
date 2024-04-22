/*

    This file contains all of the definitions for the systems in the game.

*/


#pragma once

#include <entt/entt.hpp>
#include <raylib-cpp.hpp>
#include "data/Dungeon.hpp"

void aiSystem(entt::registry& registry);
void healthSystem(entt::registry & registry);
void meleeSystem(entt::registry& registry, Dungeon& dungeon);
void rangedSystem(entt::registry& registry);
void projectileSystem(entt::registry& registry);
void onProjectileCollision(entt::registry& registry, entt::entity projectile, entt::entity other);
void playerSystem(entt::registry& registry);
void projectileSystem(entt::registry& registry);
void particleSystem(entt::registry& registry);