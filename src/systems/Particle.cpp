#include "Systems.hpp"
#include <entt/entt.hpp>
#include "Components.hpp"
#include <raylib-cpp.hpp>
#include "utils/utils.hpp"

void particleSystem(entt::registry& registry) {
    auto view = registry.view<Particle, Position, Velocity>();
    for (auto entity : view) {
        auto& particle = view.get<Particle>(entity);
        auto& position = view.get<Position>(entity);
        auto& velocity = view.get<Velocity>(entity);

        particle.lifeTime -= GetFrameTime();
        if (particle.lifeTime <= 0) {
            registry.destroy(entity);
        }

        velocity.velocity += raylib::Vector2{GetRandomValue(-1.0, 1.0), GetRandomValue(-1.0, 1.0)} * particle.random_scale;
        velocity.velocity += particle.gravity * GetFrameTime();

        
    }
}