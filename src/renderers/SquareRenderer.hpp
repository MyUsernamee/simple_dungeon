#include "renderers/Renderer.hpp"
#include <raylib-cpp.hpp>

class SquareRenderer : public Renderer {


#pragma once
    public:

        SquareRenderer(raylib::Color color);
        ~SquareRenderer();

        void render(const entt::registry& registry, const entt::entity& entity) override;

    private:

        raylib::Color color;

};