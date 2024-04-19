#pragma once

#include <raylib-cpp.hpp>
#include <entt/entt.hpp>
#include "renderable.hpp"
#include "Animation.hpp"

// TODO: Organize components and systems in a better way.

struct Player {

    raylib::Color color;
    int gamepad; // -1 if no gamepad

};

void playerSystem(entt::registry& registry);
entt::entity createPlayer(entt::registry& registry, raylib::Color color, int gamepad);
raylib::Vector2 getMovementVector(int gamepad);

class PlayerRenderer : public Renderer {

    public:

        //TODO: PLEASE ADD DOC STRINGS AND COMMENTS
        PlayerRenderer(raylib::Color color);
        ~PlayerRenderer();

        void render(const entt::registry& registry, const entt::entity& entity) override; // TODO: Implement this

    private:

        raylib::Color color;
        Animation idleAnimation;
        Animation runAnimation;

};