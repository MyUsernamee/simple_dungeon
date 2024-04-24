
#include "Components.hpp"
#include "Game.hpp"

void aiSystem(Game* game, double dt)
{

    auto &registry = game->getRegistry();

    auto view = registry.view<AI, Velocity>();

    for (auto entity : view)
    {
        auto &ai = view.get<AI>(entity);
        auto &velocity = view.get<Velocity>(entity);

        velocity.velocity = ai.movement * ai.speed;

    }

}