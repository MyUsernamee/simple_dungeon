
#include <entt/entt.hpp>
#include <raylib-cpp.hpp>

#include "Components.hpp"

class Game; // Forward declaration

/**
 * @brief Creates a dungeon spider entity.
 * 
*/
entt::entity createDungeonSpider(entt::registry& registry, raylib::Vector2 position);
