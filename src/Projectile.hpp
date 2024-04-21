#pragma once

#include <entt/entt.hpp>
#include <raylib-cpp.hpp>

void projectileSystem(entt::registry& registry);
void onProjectileCollision(entt::registry& registry, entt::entity projectile, entt::entity other);

entt::entity createProjectile(entt::registry& registry, raylib::Vector2 position, raylib::Vector2 direction, float speed, float damage);    