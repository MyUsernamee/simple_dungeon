
#include "spells/ProjectileSpell.hpp"

#include "Game.hpp"
#include <utils/TextureCache.hpp>

void ProjectileSpell::cast(Game* game, entt::entity entity, raylib::Vector2 direction)
{
    
    // Create the projectile
    auto projectile = game->getRegistry().create(); 

    Projectile projectileComponent;

    projectileComponent.speed = projectileSpeed;
    projectileComponent.lifeTime = projectileLifetime;
    projectileComponent.damage = projectileDamage;  
    projectileComponent.direction = direction;

    auto caster_collision = game->getRegistry().get<Collision>(entity);

    auto collision_bitmask = ~caster_collision.bitMask;

    game->getRegistry().emplace<Projectile>(projectile, projectileComponent);
    game->getRegistry().emplace<Velocity>(projectile, direction * projectileSpeed);
    game->getRegistry().emplace<Position>(projectile, game->getRegistry().get<Position>(entity).position);
    game->getRegistry().emplace<Size>(projectile, raylib::Vector2(projectileSize, projectileSize));
    game->getRegistry().emplace<Collision>(projectile, Collision{ collision_bitmask });
    game->getRegistry().emplace<Renderable>(projectile, LoadTextureCached("assets/particles/particle.png"));

}