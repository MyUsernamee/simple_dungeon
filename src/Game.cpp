#include "Game.hpp"
#include <entt/entt.hpp>
#include "renderable.hpp"
#include "SquareRenderer.hpp"
#include <raylib-cpp.hpp>
#include "Components.hpp"
#include "Player.hpp"
#include "AI.hpp"
#include "Enemy.hpp"
#include "Health.hpp"

Game::Game()
{

    // Initialize the camera
    camera = raylib::Camera2D(raylib::Vector2(GetRenderWidth() / 2, GetRenderHeight() / 2), raylib::Vector2(GetRenderWidth() / 2, GetRenderHeight() / 2), 0.0f, 1.0f);

    registry = entt::registry();

    // For testing lets add a renderable entity
    auto entity = registry.create();
    auto& renderable_ = registry.emplace<renderable>(entity);

    renderable_.renderer = new SquareRenderer(raylib::Color(255, 0, 0, 255));
    renderable_.z = 0;

    registry.emplace<Position>(entity, raylib::Vector2(200, 100));
    registry.emplace<Velocity>(entity, raylib::Vector2(-100, 0));
    registry.emplace<Size>(entity, raylib::Vector2(50, 50));
    registry.emplace<Health>(entity, 100, 100);
    registry.emplace<AI>(entity, 50.0, raylib::Vector2(0, 0));
    registry.emplace<MeleeEnemy>(entity, 60, 0, 80.0, 10);
    registry.emplace<Team>(entity, 0b10);
    registry.emplace<Collision>(entity, 1);

    // We add another one
    auto entity2 = registry.create();
    auto& renderable_2 = registry.emplace<renderable>(entity2);

    renderable_2.renderer = new SquareRenderer(raylib::Color(0, 255, 0, 255));
    renderable_2.z = 0;

    registry.emplace<Position>(entity2, raylib::Vector2(100, 100));
    registry.emplace<Velocity>(entity2, raylib::Vector2(100, 0));
    registry.emplace<Size>(entity2, raylib::Vector2(50, 50));
    registry.emplace<Collision>(entity2, 0b1);

    // For stress testing lets add a bunch of entities
    // for (int i = 0; i < 200; i++) {

    //     auto entity = registry.create();
    //     auto& renderable_ = registry.emplace<renderable>(entity);

    //     renderable_.renderer = new SquareRenderer(raylib::Color(255, 0, 0, 255));
    //     renderable_.z = 0;

    //     registry.emplace<Position>(entity, raylib::Vector2(GetRandomValue(0, GetRenderWidth()), GetRandomValue(0, GetRenderHeight())));
    //     registry.emplace<Velocity>(entity, raylib::Vector2(GetRandomValue(-100, 100), GetRandomValue(-100, 100)));
    //     registry.emplace<Size>(entity, raylib::Vector2(50, 50));
    //     registry.emplace<Collision>(entity, 1);

    // }

    // createPlayer(registry, raylib::Color(255, 0, 0, 255), -1);

    

}

Game::~Game()
{

    // Do nothing

}

void Game::run()
{

    update(GetFrameTime());
    render();

}

void Game::render()
{

    camera.BeginMode();

    // Sort the registry by z-index
    registry.sort<renderable>([](const renderable& a, const renderable& b) {
        return a.z < b.z;
    });

    // We then iterate over all entities with a renderable component
    auto view = registry.view<renderable>();

    for (auto entity : view) {

        auto& renderable_ = view.get<renderable>(entity);
        //TraceLog(LOG_INFO, "Rendering entity with z-index %d", renderable_.z);
        renderable_.renderer->render(registry, entity);

    }

    camera.EndMode();

    // Get everyplayer
    auto new_view = registry.view<Player, renderable>();

    for (auto entity : new_view) {

        auto& player = new_view.get<Player>(entity);
        auto& renderable_ = new_view.get<renderable>(entity);

        // Convert the renderer to a player renderer
        dynamic_cast<PlayerRenderer*>(renderable_.renderer)->statsRenderer(registry, entity);

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

    physicsSystem(dt);
    collisionSystem();
    playerSystem(registry);
    cameraFollowerSystem();
    aiSystem(registry);
    meleeSystem(registry);
    healthSystem(registry);
    

}

void Game::physicsSystem(double dt)
{

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

void Game::cameraFollowerSystem()
{

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

void Game::collisionSystem() 
{

    // This is where we will check for collisions between entities.
    auto view = registry.view<Position, Collision, Size>();

    for (auto entity : view) {

        auto& position = registry.get<Position>(entity);
        auto& collision = registry.get<Collision>(entity);
        auto& size = registry.get<Size>(entity);

        // Check for collision with other entities
        auto otherEntities = registry.view<Position, Collision>();

        for (auto otherEntity : otherEntities) {

            if (entity == otherEntity) {
                continue;
            }

            auto& otherPosition = registry.get<Position>(otherEntity);
            auto& otherCollision = registry.get<Collision>(otherEntity);
            auto& otherSize = registry.get<Size>(otherEntity);

            raylib::Rectangle rect = size.size;
            raylib::Rectangle otherRect = otherSize.size;

            rect.x = position.position.x;
            rect.y = position.position.y;

            otherRect.x = otherPosition.position.x;
            otherRect.y = otherPosition.position.y;

            if (rect.CheckCollision(otherRect) && collision.bitMask & otherCollision.bitMask) {

                // Get resolution
                raylib::Rectangle resolution_rect = rect.GetCollision(otherRect);

                raylib::Vector2 resolution = raylib::Vector2(resolution_rect.width, resolution_rect.height);\
                bool axis = abs(resolution.x) < abs(resolution.y);
                // Set the minimum resolution
                if (axis) {
                    resolution.y = 0;
                } else {
                    resolution.x = 0;
                }

                // Check if either has a velocity
                Velocity* velocity = registry.try_get<Velocity>(entity);
                Velocity* otherVelocity = registry.try_get<Velocity>(otherEntity);

                if (velocity != nullptr && otherVelocity != nullptr) {
                        
                    // Apply resolution
                    if (!axis) { // TODO: Flip this

                        float average = (velocity->velocity.y + otherVelocity->velocity.y) / 2;

                        velocity->velocity.y = average;
                        otherVelocity->velocity.y = average;
                    } else {

                        float average = (velocity->velocity.x + otherVelocity->velocity.x) / 2;

                        velocity->velocity.x = average;
                        otherVelocity->velocity.x = average;
                    }

                    position.position.x += resolution.x / 2;
                    position.position.y += resolution.y / 2;

                    otherPosition.position.x -= resolution.x / 2;
                    otherPosition.position.y -= resolution.y / 2;
                }
                else if (velocity != nullptr) {
                    if (axis) {
                        velocity->velocity.y = 0;
                    } else {
                        velocity->velocity.x = 0;
                    }

                    position.position.x += resolution.x;
                    position.position.y += resolution.y;
                }
                else if (otherVelocity != nullptr) {
                    if (axis) {
                        otherVelocity->velocity.y = 0;
                    } else {
                        otherVelocity->velocity.x = 0;
                    }

                    otherPosition.position.x -= resolution.x;
                    otherPosition.position.y -= resolution.y;
                }

            }

        }

    }

}