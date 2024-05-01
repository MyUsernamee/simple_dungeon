/*

    This file contains all of the definitions for the systems in the game.

*/


#pragma once

#include <entt/entt.hpp>
#include <raylib-cpp.hpp>

class Game; // Forward declaration

void aiSystem(Game* game, double dt);
void healthSystem(Game* game, double dt);
void meleeSystem(Game* game, double dt);
void rangedSystem(Game* game, double dt);
void projectileSystem(Game* game, double dt);
void playerSystem(Game* game, double dt);
void projectileSystem(Game* game, double dt);
void particleSystem(Game* game, double dt);
void physicsSystem(Game* game, double dt);
void collisionSystem(Game* game, double dt);
void cameraFollowerSystem(Game* game, double dt);
void spellCastSystem(Game* game, double dt);
void particleSystemRegistry(entt::registry& registry, double dt);
void animationSystem(Game* game, double dt);
void particleSystemSystem(Game* game, double dt); // Werid name lmao


std::vector<std::function<void(Game*, double)>> getSystems();
