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
    currentDungeon = Dungeon(0, 0, nullptr, TileSet()); // Empty dungeon
    registry = entt::registry();

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

    std::vector<raylib::Vector2> visibility_points;

    // We get all players
    auto _view = registry.view<Player, Position>();

    for (auto entity : _view) {

        auto& position = _view.get<Position>(entity);
        visibility_points.push_back(position.position);

    }

    currentDungeon.render(camera, visibility_points);

    raylib::Vector2 start = camera.target;
    raylib::Vector2 end = camera.GetScreenToWorld(GetMousePosition());

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {

        // Find a path from the player to the mouse
        std::vector<raylib::Vector2> path = currentDungeon.pathFind(start, end);

        if (path.size() > 0) {

            for (int i = 0; i < path.size() - 1; i++) {

                DrawLine(path[i].x, path[i].y, path[i + 1].x, path[i + 1].y, raylib::Color(255, 0, 0, 255));

            }

        }

    }

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
    meleeSystem(registry, currentDungeon);
    healthSystem(registry);

    // If the user presses r we spawn an enemy at the mouse position
    if (IsKeyPressed(KEY_R)) {

        auto entity = registry.create();
        
        auto& renderable_ = registry.emplace<renderable>(entity);

        renderable_.renderer = new SquareRenderer(raylib::Color(0, 255, 0, 255));
        renderable_.z = 0;

        registry.emplace<Position>(entity, camera.GetScreenToWorld(GetMousePosition()));
        registry.emplace<Velocity>(entity, raylib::Vector2(GetRandomValue(-100, 100), GetRandomValue(-100, 100)));
        registry.emplace<Size>(entity, raylib::Vector2(50, 50));
        registry.emplace<Collision>(entity, 0b1);
        registry.emplace<Health>(entity, 100, 100);
        registry.emplace<AI>(entity, 50.0, raylib::Vector2(0, 0));
        registry.emplace<MeleeEnemy>(entity, 60, 0, 80.0, 10);
        registry.emplace<Team>(entity, 0b10);

    }
    

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

            auto center = position.position + size.size / 2;
            auto otherCenter = otherPosition.position + otherSize.size / 2;

            if (center.Distance(otherCenter) < (size.size.x + otherSize.size.x) / 2.0 && collision.bitMask & otherCollision.bitMask) {


                raylib::Vector2 resolution = center - otherCenter;

                resolution = resolution.Normalize();
                resolution = resolution * ((size.size.x + otherSize.size.x) / 2.0 - center.Distance(otherCenter));

                // Check if either has a velocity
                Velocity* velocity = registry.try_get<Velocity>(entity);
                Velocity* otherVelocity = registry.try_get<Velocity>(otherEntity);

                if (velocity != nullptr && otherVelocity != nullptr) {
                      
                    float average = (velocity->velocity.y + otherVelocity->velocity.y) / 2;

                    position.position.x += resolution.x / 2;
                    position.position.y += resolution.y / 2;

                    otherPosition.position.x -= resolution.x / 2;
                    otherPosition.position.y -= resolution.y / 2;
                }
                else if (velocity != nullptr) {
                    
                    // We set the velocity to 0 in the direction of the resolution
                    float dot = velocity->velocity.DotProduct(resolution);

                    if (dot > 0) {
                        velocity->velocity = velocity->velocity - resolution * dot / resolution.LengthSqr();
                    }

                    position.position.x += resolution.x;
                    position.position.y += resolution.y;
                }
                else if (otherVelocity != nullptr) {
                    
                    // We set the velocity to 0 in the direction of the resolution
                    float dot = otherVelocity->velocity.DotProduct(resolution);

                    if (dot > 0) {
                        otherVelocity->velocity = otherVelocity->velocity - resolution * dot / resolution.LengthSqr();
                    }

                    otherPosition.position.x -= resolution.x;
                    otherPosition.position.y -= resolution.y;
                }

            }

        }

        // We now do collisions with the dungeon
        raylib::Rectangle rect = size.size;
        rect.x = position.position.x;
        rect.y = position.position.y;

        // We get all tiles within the rectangle
        int x1 = rect.x / TILE_SIZE;
        int y1 = rect.y / TILE_SIZE;

        int x2 = (rect.x + rect.width) / TILE_SIZE + 1;
        int y2 = (rect.y + rect.height) / TILE_SIZE + 1;

        for (int y = y1; y <= y2; y++) {

            for (int x = x1; x <= x2; x++) {

                if (x < 0 || y < 0 || x >= currentDungeon.width || y >= currentDungeon.height) {
                    continue;
                }

                if (currentDungeon.getTile(x, y).solid) {

                    raylib::Rectangle tileRect = raylib::Rectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);

                    // Get the closest point on the rectangle to the center of the entity
                    raylib::Vector2 center = position.position + size.size / 2;
                    raylib::Vector2 closest = center;
                    closest.x = std::clamp(closest.x, tileRect.x, tileRect.x + tileRect.width);
                    closest.y = std::clamp(closest.y, tileRect.y, tileRect.y + tileRect.height);

                    if (closest.Distance(center) < size.size.x / 2) {

                        // We have a collision
                        raylib::Vector2 resolution = center - closest;

                        resolution = resolution.Normalize();
                        resolution = resolution * (size.size.x / 2 - closest.Distance(center));

                        // Check if either has a velocity
                        Velocity* velocity = registry.try_get<Velocity>(entity);

                        if (velocity != nullptr) {
                            
                            // We set the velocity to 0 in the direction of the resolution
                            float dot = velocity->velocity.DotProduct(resolution);

                            if (dot > 0) {
                                velocity->velocity = velocity->velocity - resolution * dot / resolution.LengthSqr();
                            }

                            position.position.x += resolution.x;
                            position.position.y += resolution.y;
                        }

                    }



                }

            }

        }

    }

}