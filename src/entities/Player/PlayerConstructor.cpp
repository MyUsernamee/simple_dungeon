
#include "Constructors.hpp"
#include "Components.hpp"
#include "utils/TextureCache.hpp"
#include "Game.hpp"

entt::entity createPlayer(entt::registry &registry, raylib::Color color, int gamepad, raylib::Vector2 position)
{
    auto player = registry.create();
    auto& Renderable_player = registry.emplace<Renderable>(player);

    Renderable_player.color = color;

    int count = 0;
    raylib::Vector2 available_position = raylib::Vector2(0, 0);
    for (auto entity : registry.view<Player, Position>())
    {
        count++;
        available_position = registry.get<Position>(entity).position;
    }

    auto idleAnimation = Animation("assets/tileset/frames/skelet_idle_anim_f%d.png");
    auto runAnimation = Animation("assets/tileset/frames/skelet_run_anim_f%d.png");

    auto animations = std::vector<Animation>{idleAnimation, runAnimation};

    registry.emplace<Position>(player, position);
    TraceLog(LOG_INFO, "Player created at %f, %f", position.x, position.y);
    registry.emplace<Velocity>(player, raylib::Vector2(0, 0));
    registry.emplace<Size>(player, raylib::Vector2(32, 32));
    registry.emplace<Collision>(player, 0b1);
    registry.emplace<Player>(player, color, gamepad);
    registry.emplace<CameraFollower>(player, 1, raylib::Vector2(25, 25));
    registry.emplace<Team>(player, 0b01);
    registry.emplace<SpellCaster>(player);
    registry.emplace<Animator>(player, animations, 0, 0.1f);
    //registry.emplace<Light>(player, 64);

    auto cursor = registry.create();
    registry.emplace<Position>(cursor, position);
    registry.emplace<Renderable>(cursor, LoadTextureCached("assets/cursor.png"), raylib::Color{255, 255, 255, 255});
    registry.emplace<Size>(cursor, raylib::Vector2(8, 8));
    registry.emplace<CameraFollower>(cursor, 1, raylib::Vector2(8, 8));

    registry.get<Player>(player).cursorEntity = cursor;

    registry.emplace<Health>(player, 100, 100, 
        [player](Game* game, entt::entity entity)
        {
            auto &player_component = game->getRegistry().get<Player>(player);
            game->getRegistry().destroy(player_component.cursorEntity);
        });

    if (count > 2)
    {
        registry.get<Position>(player).position = available_position;
    }

    return player;
}