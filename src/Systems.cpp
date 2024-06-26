
#include "Systems.hpp"

std::vector<std::function<void(Game*, double)>> getSystems() {
    std::vector<std::function<void(Game*, double)>> systems;

    systems.push_back(physicsSystem);
    systems.push_back(collisionSystem);
    systems.push_back(cameraFollowerSystem);
    systems.push_back(aiSystem);
    systems.push_back(healthSystem);
    systems.push_back(projectileSystem);
    systems.push_back(playerSystem);
    systems.push_back(particleSystem);
    systems.push_back(animationSystem);
    systems.push_back(particleSystemSystem);
    systems.push_back(spellCastSystem);

    return systems;
}