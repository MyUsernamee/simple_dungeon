#include "Enemy.hpp"
#include "Components.hpp"

#include <raylib-cpp.hpp>

void meleeSystem(entt::registry & registry)
{

    auto view = registry.view<AI, MeleeEnemy, Team, Position>();

    for (auto entity : view)
    {
        auto &ai = view.get<AI>(entity);
        auto &melee = view.get<MeleeEnemy>(entity);
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

            raylib::Vector2 direction = enemyPosition.position - position.position;
            direction = direction.Normalize(); // TODO: Add a visibility check.

            ai.movement = direction;
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