#include "Projectile.hpp"
#include "Components.hpp"

void projectileSystem(entt::registry &registry)
{

    auto view = registry.view<Projectile, Position, Velocity>();
    for (auto entity : view)
    {
        auto &projectile = view.get<Projectile>(entity);
        auto &position = view.get<Position>(entity);
        auto &velocity = view.get<Velocity>(entity);

        position.position += velocity.velocity;

        projectile.lifeTime--;
        if (projectile.lifeTime <= 0)
        {
            registry.destroy(entity);
        }
    }

}

void onProjectileCollision(entt::registry &registry, entt::entity projectile, entt::entity other)
{

    auto &projectileCollision = registry.get<Collision>(projectile);
    auto &otherCollision = registry.get<Collision>(other);
    auto &projectile_ = registry.get<Projectile>(projectile);
    auto &otherHealth = registry.get<Health>(other);

    otherHealth.health -= projectile_.damage;

    registry.destroy(projectile);

}

entt::entity createProjectile(entt::registry &registry, raylib::Vector2 position, raylib::Vector2 direction, float speed, float damage)
{
    
    auto entity = registry.create();

    registry.emplace<Projectile>(entity, damage, 60 * 10, speed);
    registry.emplace<Velocity>(entity, direction * speed);
    registry.emplace<Position>(entity, position);
    registry.emplace<Collision>(entity, 0b11111111);

    entt::sink collisionSink {registry.get<Collision>(entity).onCollisionSignal};
    collisionSink.connect<&onProjectileCollision>();


}
