
#pragma once

#include <entt/entt.hpp>
#include <raylib-cpp.hpp>

#include "utils/TextureCache.hpp"
#include "Components.hpp"

#include "Game.hpp"

void createCandle(Game* game, raylib::Vector2 position) {

    auto& registry = game->getRegistry();

    auto entity = registry.create();

    registry.emplace<Position>(entity, position);
    registry.emplace<Size>(entity, raylib::Vector2{32, 32});
    registry.emplace<Collision>(entity, 0b00000001);
    registry.emplace<Renderable>(entity, LoadTextureCached("assets/candle.png"), raylib::Color{255, 255, 255, 255});
    registry.emplace<Light>(entity, 8, raylib::Color{255, 255, 255, 255});

}