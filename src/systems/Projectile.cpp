#include "Systems.hpp"
#include "Components.hpp"
#include "renderers/SquareRenderer.hpp"

void projectileSystem(entt::registry &registry)
{

    auto view = registry.view<Projectile, Position, Velocity, Collision>();
    for (auto entity : view)
    {
        auto &projectile = view.get<Projectile>(entity);
        auto &position = view.get<Position>(entity);
        auto &velocity = view.get<Velocity>(entity);
        auto &collision = view.get<Collision>(entity);

        velocity.velocity = projectile.direction.Normalize() * projectile.speed;

        projectile.lifeTime--;
        if (projectile.lifeTime <= 0)
        {
            registry.destroy(entity);
        }

        if (collision.collisions.size() > 0)
        {
            for (auto other : collision.collisions)
            {
                
                // Check to make sure the other entity is still valid
                if (!registry.valid(other) && other != entt::null) // Entt::null is the map
                {
                    continue;
                }

                auto* otherHealth = registry.try_get<Health>(other);
                if (otherHealth)
                {
                    otherHealth->takeDamage(projectile.damage);
                }

                if (registry.valid(entity))
                {
                    registry.destroy(entity);
                }

            }
        }

    }

}

entt::entity createProjectile(entt::registry &registry, raylib::Vector2 position, raylib::Vector2 direction, float speed, float damage)
{
    
    auto entity = registry.create();

    registry.emplace<Projectile>(entity, damage, 60 * 1, speed, direction);
    registry.emplace<Velocity>(entity, direction * speed);
    registry.emplace<Position>(entity, position);
    registry.emplace<Collision>(entity, 0b11111111);
    registry.emplace<Size>(entity, raylib::Vector2(10, 10));
    registry.emplace<Renderable>(entity, new SquareRenderer(raylib::Color(255, 0, 0, 255)));
    return entity;


}