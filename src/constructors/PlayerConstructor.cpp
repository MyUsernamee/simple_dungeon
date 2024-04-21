
#include "Constructors.hpp"
#include "renderers/PlayerRenderer.hpp"
#include "Components.hpp"

entt::entity createPlayer(entt::registry &registry, raylib::Color color, int gamepad, raylib::Vector2 position)
{
    auto player = registry.create();
    auto& Renderable_player = registry.emplace<Renderable>(player);

    Renderable_player.renderer = new PlayerRenderer(color);
    Renderable_player.z = 0;

    int count = 0;
    raylib::Vector2 available_position = raylib::Vector2(0, 0);
    for (auto entity : registry.view<Player, Position>())
    {
        count++;
        available_position = registry.get<Position>(entity).position;
    }

    registry.emplace<Position>(player, position);
    TraceLog(LOG_INFO, "Player created at %f, %f", position.x, position.y);
    registry.emplace<Velocity>(player, raylib::Vector2(0, 0));
    registry.emplace<Size>(player, raylib::Vector2(32, 32));
    registry.emplace<Collision>(player, 0b1);
    registry.emplace<Player>(player, color, gamepad);
    registry.emplace<CameraFollower>(player, 1, raylib::Vector2(25, 25));
    registry.emplace<Health>(player, 100, 100);
    registry.emplace<Team>(player, 0b01);

    

    if (count > 2)
    {
        registry.get<Position>(player).position = available_position;
    }

    return player;
}