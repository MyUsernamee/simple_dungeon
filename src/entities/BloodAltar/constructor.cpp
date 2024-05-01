#include "Game.hpp"
#include "entities/BloodAltar/BloodAltar.hpp"
#include "Components.hpp"
#include <utils/TextureCache.hpp>

void createBloodAltar(Game* game, raylib::Vector2 position)
{

    auto& registry = game->getRegistry();

    auto entity = registry.create();
    registry.emplace<Position>(entity, position);
    registry.emplace<Size>(entity, raylib::Vector2{ 32, 32 });
    registry.emplace<Collision>(entity, 1);
    registry.emplace<BloodAltarComponent>(entity);
    registry.emplace<Renderable>(entity, LoadTextureCached("assets/Blood_Alter.png"), WHITE);
    ParticleSystem particleSystem;
    particleSystem.spawnRate = 0.1;
    particleSystem.spawnTimer = 0.1;
    particleSystem.spawnRadius = 16;
    particleSystem.particle = Particle{ raylib::Vector2{0, -10}, raylib::Vector2{1.0, 0.0}, 4 };
    registry.emplace<ParticleSystem>(entity, particleSystem);
    Animation glowAnimation = Animation("assets/Blood Alter/Blood Alter%d.png");
    registry.emplace<Animator>(entity, std::vector<Animation>{glowAnimation}, 0, 0, 0.0f, 2);
    registry.emplace<Light>(entity, 4, raylib::Color{ 200, 0, 0, 255 });

}