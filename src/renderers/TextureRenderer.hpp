#include "renderers/Renderer.hpp"
#include <raylib-cpp.hpp>

#pragma once

class TextureRenderer : public Renderer {

    public:

        TextureRenderer(raylib::Color color, Texture2D texture) : color(color) {
            this->texture = texture;
        }
        ~TextureRenderer();

        void render(const entt::registry& registry, const entt::entity& entity) override;

    private:

        raylib::Color color;
        Texture2D texture;

};