#pragma once

#include <raylib-cpp.hpp>
#include <entt/entt.hpp>
#include "utils/Animation.hpp"
#include "Renderer.hpp"

// TODO: Organize components and systems in a better way.

class PlayerRenderer : public Renderer {

    public:

        //TODO: PLEASE ADD DOC STRINGS AND COMMENTS
        PlayerRenderer(raylib::Color color);
        ~PlayerRenderer();

        void render(const entt::registry& registry, const entt::entity& entity) override; // TODO: Implement this
        void statsRenderer(entt::registry& registry, const entt::entity& entity);

    private:

        raylib::Color color;
        Animation idleAnimation;
        Animation runAnimation;

};