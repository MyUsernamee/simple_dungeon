#include "Constructors.hpp"

#include <entt/entt.hpp>
#include <raylib-cpp.hpp>
#include "renderers/TextureRenderer.hpp"
#include <Components.hpp>

entt::entity createParticle(entt::registry& registry, raylib::Vector2 position, raylib::Vector2 velocity, Texture2D texture, raylib::Vector2 random_scale, raylib::Vector2 gravity, double lifeTime, raylib::Color color) {

    auto entity = registry.create();

    registry.emplace<Particle>(entity, gravity, random_scale, lifeTime, texture, color);
    registry.emplace<Velocity>(entity, velocity);
    registry.emplace<Position>(entity, position);
    registry.emplace<Size>(entity, raylib::Vector2(texture.width, texture.height));
    registry.emplace<Renderable>(entity, new TextureRenderer(color, texture), 2);

    return entity;

}