#include "TextureRenderer.hpp"
#include <entt/entt.hpp>
#include "Components.hpp"



void TextureRenderer::render(const entt::registry & registry, const entt::entity & entity)
{

    auto& transform = registry.get<Position>(entity);
    auto& size = registry.get<Size>(entity);

    raylib::Rectangle rect = raylib::Rectangle(transform.position.x, transform.position.y, size.size.x, size.size.y);

    DrawTexture(texture, transform.position.x, transform.position.y, color);

    // For Debug rednering
    //rect.Draw(color);

}