#include "Spells.hpp"
#include "Components.hpp"
#include "renderers/SquareRenderer.hpp"

void castFireball(Game* game, entt::entity proj, entt::entity other)
{
    auto& registry = game->getRegistry();

    auto position = registry.get<Position>(proj).position;
    
    auto entity = registry.create();
    registry.emplace<Position>(entity, position);
    registry.emplace<Velocity>(entity, raylib::Vector2{0, 0});
    registry.emplace<Renderable>(entity, new SquareRenderer(raylib::Color{255, 0, 0, 255}), 1);
    registry.emplace<Size>(entity, raylib::Vector2{16, 16});
    //registry.emplace<Collision>(entity, 0b10);

}