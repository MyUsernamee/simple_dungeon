
#include "Components.hpp"
#include "Constructors.hpp"
#include <utils/CastTexture.hpp>

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