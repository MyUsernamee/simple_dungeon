#include "DungeonSpider.hpp"
#include "Components.hpp"
#include "Game.hpp"

void DungeonSpider::update(Game *game, entt::entity entity)
{

    auto& registry = game->getRegistry();

    auto &position = registry.get<Position>(entity);
    auto &velocity = registry.get<Velocity>(entity);
    auto &ai = registry.get<AI>(entity);

    auto &dungeon = game->getDungeon();

    switch (state)
    {
    case State::IDLE:
        //ai.updateTarget(position.position);
        if (GetRandomValue(0, 100) < 1)
        {
            state = State::WALKING;

            raylib::Vector2 grid_position = raylib::Vector2{static_cast<int>(position.position.x / TILE_SIZE), static_cast<int>(position.position.y / TILE_SIZE)};

            raylib::Vector2 newPosition = raylib::Vector2{GetRandomValue(0, dungeon.getWidth()), GetRandomValue(0, dungeon.getHeight())};

            while (dungeon.getTile(newPosition.x, newPosition.y).getBoolProperty("solid") || dungeon.getTile(newPosition.x, newPosition.y).textures.size() == 0)
            {
                newPosition = raylib::Vector2{GetRandomValue(0, dungeon.getWidth()), GetRandomValue(0, dungeon.getHeight())};
            }

            ai.updateTarget(newPosition * TILE_SIZE);

        }
        break;
    case State::WALKING:

        if (ai.path.size() == 0)
        {
            state = State::IDLE;
        }

        break;
    
    default:
        break;
    }

}