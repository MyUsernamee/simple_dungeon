
/*

    This is where all creation of entities goes.
    For instance, creating a player entity would go here.

*/

#pragma once

#include <entt/entt.hpp>
#include <raylib-cpp.hpp>

entt::entity createPlayer(entt::registry& registry, raylib::Color color, int gamepad, raylib::Vector2 position = raylib::Vector2(512, 512));