
#include "Components.hpp"

void aiSystem(entt::registry &registry)
{

    auto view = registry.view<AI, Velocity>();

    for (auto entity : view)
    {
        auto &ai = view.get<AI>(entity);
        auto &velocity = view.get<Velocity>(entity);

        velocity.velocity = ai.movement * ai.speed;

    }

}