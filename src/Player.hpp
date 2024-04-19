#pragma once

#include <raylib-cpp.hpp>
#include <entt/entt.hpp>
#include "renderable.hpp"

// TODO: Organize components and systems in a better way.

struct Player {

    raylib::Color color;
    int gamepad; // -1 if no gamepad

};

void playerSystem(entt::registry& registry);
raylib::Vector2 getMovementVector(int gamepad);

class PlayerRenderer : public Renderer {

    public:

        PlayerRenderer(raylib::Color color);
        ~PlayerRenderer();

        void render(const entt::registry& registry, const entt::entity& entity) override; // TODO: Implement this

    private:

        raylib::Color color;

};