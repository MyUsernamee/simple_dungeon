
#include "Systems.hpp"
#include "Components.hpp"
#include <entt/entt.hpp>
#include <raylib-cpp.hpp>
#include "Game.hpp"

void cameraFollowerSystem(Game* game, double dt)
{

    auto& registry = game->getRegistry();
    auto& camera = game->getCamera();
    

    // This is where we will update the camera to follow the player.
    auto view = registry.view<Position, CameraFollower>();

    raylib::Vector2 average = raylib::Vector2(0, 0);
    int count = 0;

    for (auto entity : view) {

        auto& position = view.get<Position>(entity);
        auto& cameraFollower = view.get<CameraFollower>(entity);

        average += position.position + cameraFollower.offset; // TODO: Take into account strength
        count++;

    }

    if (count == 0) {
        return;
    }

    average /= count;

    raylib::Vector2 target = camera.target; // Convert to raylib::Vector2 from Vector2

    target += (average - target) * 0.1; // TODO: Create seperate function / variable for this and make it a component
    camera.target = target; // Convert back to Vector2 from raylib::Vector2

}
