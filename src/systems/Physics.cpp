
#include "Game.hpp"
#include "Components.hpp"

void physicsSystem(Game* game, double dt)
{

    auto& registry = game->getRegistry();

    // This is where we will apply physics to entities.
    auto view = registry.view<Position, Velocity>();

    for (auto entity : view) {

        auto& position = view.get<Position>(entity);
        auto& velocity = view.get<Velocity>(entity);

        position.position.x += velocity.velocity.x * dt;
        position.position.y += velocity.velocity.y * dt;

        velocity.velocity *= 0.9; // TODO: Create seperate function / variable for this and make it a component

    }

}