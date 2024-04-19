#include "Health.hpp"

#include "Components.hpp"


void healthSystem(entt::registry & registry)
{

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