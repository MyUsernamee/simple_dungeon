
#include "Components.hpp"
#include "data/Dungeon.hpp"

#include <raylib-cpp.hpp>
#include "utils/AStar.hpp"
#include "Game.hpp"

void meleeSystem(Game* game, double dt)
{

    auto &registry = game->getRegistry();
    // Get the dungeon from the game.
    auto &dungeon = game->getDungeon();

    auto view = registry.view<AI, MeleeEnemy, Team, Position, Size>();

    for (auto entity : view)
    {
        auto &ai = view.get<AI>(entity);
        auto &melee = view.get<MeleeEnemy>(entity);
        auto &size = view.get<Size>(entity);
        auto &position = view.get<Position>(entity);
        auto &team = view.get<Team>(entity);

        // We get the closest enemy on a team that isn't friends with us.
        entt::entity closestEnemy = entt::null;
        float closestDistance = std::numeric_limits<float>::max();

        auto enemyView = registry.view<Position, Health, Team>();

        for (auto enemy : enemyView)
        {
            auto &enemyPosition = enemyView.get<Position>(enemy);
            auto &enemyTeam = enemyView.get<Team>(enemy);

            if (team.teamBitMask & enemyTeam.teamBitMask)
            {
                continue; // They are on the same team. or friends.
            }

            float distance = position.position.Distance(enemyPosition.position);

            if (distance < closestDistance)
            {
                closestDistance = distance;
                closestEnemy = enemy;
            }
        }


        if (closestEnemy != entt::null)
        {

            auto &enemyPosition = enemyView.get<Position>(closestEnemy);

            raylib::Vector2 center = position.position + size.size / 2.0;

            if (dungeon.rayCast(center, enemyPosition.position, nullptr))
            {
                continue; // We can't see the enemy.
            }

            // We look for a path to the enemy.
            auto path = dungeon.pathFind(center, enemyPosition.position);

            if (path.size() > 0)
            {

                raylib::Vector2 positionToMoveTo = path[1] + raylib::Vector2{0.5, 0.5} * TILE_SIZE;

                raylib::Vector2 direction = positionToMoveTo - center;
                direction = direction.Normalize();
                ai.movement = direction;

            }
            else
            {
                ai.movement = raylib::Vector2{0, 0};
            }

            
        }
        else
        {
            ai.movement = raylib::Vector2{0, 0};
        }

        if (closestDistance < melee.range && melee.attackTimer <= 0)
        {
            melee.attackTimer = melee.attackSpeed;

            // Attack the enemy.
            auto &enemyHealth = enemyView.get<Health>(closestEnemy);
            enemyHealth.takeDamage(melee.damage);

        }
        else if (melee.attackTimer > 0)
        {
            melee.attackTimer--;
        }

    }

}