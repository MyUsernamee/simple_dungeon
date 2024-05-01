
#include "Components.hpp"

#include <raylib-cpp.hpp>
#include <entt/entt.hpp>

#include "Game.hpp"
#include "Systems.hpp"
#include <utils/TextureCache.hpp>

void particleSystemSystem(Game* game, double dt) {

    auto& registry = game->getRegistry();
    
    auto view = registry.view<ParticleSystem, Position>();

    for (auto entity : view) {
        auto& particleSystem = view.get<ParticleSystem>(entity);
        auto& position = view.get<Position>(entity);
        
        // Remove invalid particles
        for (int i = 0; i < particleSystem.particles.size(); i++) {
            if (!registry.valid(particleSystem.particles[i])) {
                particleSystem.particles.erase(particleSystem.particles.begin() + i);
                i--;
            }
        }

        // Spawn new particles
        
        if (particleSystem.spawnTimer <= 0) {
            
            auto particle = registry.create();
            registry.emplace<Position>(particle, position.position + raylib::Vector2{GetRandomValue(-particleSystem.spawnRadius, particleSystem.spawnRadius), GetRandomValue(-particleSystem.spawnRadius, particleSystem.spawnRadius)});
            registry.emplace<Velocity>(particle, raylib::Vector2{GetRandomValue(-1.0, 1.0), GetRandomValue(-1.0, 1.0)});
            registry.emplace<Particle>(particle, particleSystem.particle);
            registry.emplace<Size>(particle, raylib::Vector2{2, 2});
            registry.emplace<Glow>(particle, 16);
            registry.emplace<Renderable>(particle, LoadTextureCached("assets/particles/particle.png"), RED, 1);
            particleSystem.particles.push_back(particle);

            particleSystem.spawnTimer = particleSystem.spawnRate;
        } else {
            particleSystem.spawnTimer -= dt;
        }

    }

}