
#include "Components.hpp"
#include "Game.hpp"

double distance_heuristic(raylib::Vector2 a, raylib::Vector2 b, int type)
{
    return a.Distance(b);
}

void aiSystem(Game* game, double dt)
{

    auto &registry = game->getRegistry();

    auto view = registry.view<AI, Velocity>();

    for (auto entity : view)
    {
        auto &ai = view.get<AI>(entity);
        auto &velocity = view.get<Velocity>(entity);

        ai.brain->update(game, entity);

        if (ai.updatePath)
        {
            // Update path
            ai.updatePath = false;

            // Pathfind
            ai.path = game->getDungeon().pathFind(registry.get<Position>(entity).position, ai.getTarget());
        }

        // Get the next position
        if (ai.path.size() > 0)
        {
            raylib::Vector2 nextPosition = ai.path[0];

            // Move towards the next position
            raylib::Vector2 direction = nextPosition - registry.get<Position>(entity).position;
            direction = direction.Normalize();
            velocity.velocity = direction * ai.speed;

            // Check if we are at the next position
            if (registry.get<Position>(entity).position.Distance(nextPosition) < 5) // TODO: Remove magic number
            {
                ai.path.erase(ai.path.begin());
            }
        }
        else
            velocity.velocity *= 0;

    }

}

void AI::updateTarget(raylib::Vector2 target)
{
    
    this->target = target;
    this->updatePath = true;

}

raylib::Vector2 AI::getTarget()
{
    return target;
}