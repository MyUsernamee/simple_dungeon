
#pragma once

#include <entt/entt.hpp>

class Game; // Forward declaration

/**
 * @brief Simple class that defines the behavior of a npc.
*/
class AiBrain {
public:
    virtual void update(Game* game, entt::entity entity) = 0;
};