
/*

    This is where all creation of entities goes.
    For instance, creating a player entity would go here.

*/

#pragma once

#include <entt/entt.hpp>
#include <raylib-cpp.hpp>

entt::entity createPlayer(entt::registry& registry, raylib::Color color, int gamepad, raylib::Vector2 position = raylib::Vector2(512, 512));
entt::entity createProjectile(entt::registry& registry, raylib::Vector2 position, raylib::Vector2 direction, float speed, float damage);
entt::entity createParticle(entt::registry& registry, raylib::Vector2 position, raylib::Vector2 velocity, Texture2D texture, raylib::Vector2 random_scale, raylib::Vector2 gravity, double lifeTime, raylib::Color color);