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
        if (GetRandomValue(0, 100) < 1)
        {
            state = State::WALKING;

            raylib::Vector2 newPosition = raylib::Vector2{GetRandomValue(0, dungeon.width), GetRandomValue(0, dungeon.height)};

            while (dungeon.getTile(newPosition.x, newPosition.y).getBoolProperty("solid"))
            {
                newPosition = raylib::Vector2{GetRandomValue(0, dungeon.width), GetRandomValue(0, dungeon.height)};
            }

            ai.updateTarget(newPosition);

        }
        break;
    case State::WALKING:

        if (ai.getTarget().Distance(position.position) < 10)
        {
            state = State::IDLE;
        }

        break;
    
    default:
        break;
    }

}