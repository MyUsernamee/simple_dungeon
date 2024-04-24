
#include "Systems.hpp"
#include "Components.hpp"
#include "Game.hpp"
#include "data/Dungeon.hpp"

void collisionSystem(Game* game, double dt)
{

    auto& registry = game->getRegistry();

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

                collision.collisions.push_back(otherEntity);
                otherCollision.collisions.push_back(entity);

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

        auto dungeon_view = registry.view<Dungeon>();
        auto dungeon_entity = *dungeon_view.begin();
        auto& currentDungeon = registry.get<Dungeon>(dungeon_entity);

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

                        collision.collisions.push_back(entt::null);

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