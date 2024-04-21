#include "renderers/SquareRenderer.hpp"
#include "Components.hpp"

SquareRenderer::SquareRenderer(raylib::Color color)
{
    this->color = color;

}

SquareRenderer::~SquareRenderer()
{

    // Do nothing

}

void SquareRenderer::render(const entt::registry& registry, const entt::entity& entity)
{

    auto& transform = registry.get<Position>(entity);
    auto& size = registry.get<Size>(entity);

    raylib::Rectangle rect = raylib::Rectangle(transform.position.x, transform.position.y, size.size.x, size.size.y);

    rect.Draw(color);

}