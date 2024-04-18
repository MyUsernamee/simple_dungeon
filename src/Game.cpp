#include "Game.hpp"
#include <entt/entt.hpp>
#include "renderable.hpp"

Game::Game()
{

    registry = entt::registry();

}

Game::~Game()
{

    // Do nothing

}

void Game::run()
{

    update(1.0 / 60.0);
    render();

}

void Game::render()
{

    // Sort the registry by z-index
    registry.sort<renderable>([](const renderable& a, const renderable& b) {
        return a.z < b.z;
    });

    // We then iterate over all entities with a renderable component
    auto view = registry.view<renderable>();

    for (auto entity : view) {

        auto& renderable_ = view.get<renderable>(entity);
        renderable_.render(registry, entity);

    }

}

void Game::update(double dt)
{

    // This is where literally all of the game logic will happen. Will definetly need to be broken up into smaller functions.
    // collisionSystem();
    // playerSystem();
    // enemySystem();
    // projectileSystem();
    // updateCamera();
    // 

}