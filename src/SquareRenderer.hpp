#include "renderable.hpp"
#include <raylib-cpp.hpp>

#pragma once

class SquareRenderer : public Renderer {

    public:

        SquareRenderer(raylib::Color color);
        ~SquareRenderer();

        void render(const entt::registry& registry, const entt::entity& entity) override;

    private:

        raylib::Color color;

};