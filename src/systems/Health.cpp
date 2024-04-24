

#include "Components.hpp"
#include "Game.hpp"

void healthSystem(Game* game, double dt)
{

    auto &registry = game->getRegistry();

    auto view = registry.view<Health>();

    for (auto entity : view)
    {
        auto &health = view.get<Health>(entity);

        if (health.health <= 0)
        {
            registry.destroy(entity);
        }
    }
    
}