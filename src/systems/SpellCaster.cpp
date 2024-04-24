
#include "Components.hpp"
#include "Constructors.hpp"
#include <utils/CastTexture.hpp>
#include "Game.hpp"
#include "spells/Spells.hpp"

void SpellCaster::addCastDirection(entt::registry &registry, raylib::Vector2 position, CastDirection direction) {

    createParticle(
        registry,
        position,
        raylib::Vector2{0, 0},
        castDirectionToTexture(direction),
        raylib::Vector2{10.0, 0.0},
        raylib::Vector2{0, -500.0},
        1.0,
        raylib::Color{255, 255, 255, 255}
    );

    currentCastDirections.push_back(direction);

}

void SpellCaster::cast(Game* game, entt::entity entity, raylib::Vector2 direction) {

    auto spells = game->getSpells();

    auto position = game->getRegistry().get<Position>(entity).position + game->getRegistry().get<Size>(entity).size / 2;
    position += direction * game->getRegistry().get<Size>(entity).size.x * 2.0;


    // We find the matching spells
    for (auto spell : spells) {

        if (spell.castDirections == currentCastDirections) {

            // Create a new projectile that copies the spell's projectile
            auto proj = createProjectile(
                game->getRegistry(),
                position,
                direction,
                spell.projectile.speed,
                spell.projectile.damage
            );

            auto& projectile = game->getRegistry().get<Projectile>(proj);
            projectile.onHit = castFireball;
            currentCastDirections.clear();
            return;

        }

    }

    currentCastDirections.clear(); // Failed

}