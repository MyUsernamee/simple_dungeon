#include "SpellCasterRenderer.hpp"
#include "Components.hpp"
#include "utils/CastTexture.hpp"

void spellCasterRenderer(entt::registry &registry)
{

    auto view = registry.view<SpellCaster, Position, Size>();

    for (auto entity : view)
    {
        auto &spellCaster = view.get<SpellCaster>(entity);
        auto &position = view.get<Position>(entity);
        auto &size = view.get<Size>(entity);

        raylib::Vector2 direction_center = raylib::Vector2{position.position.x + size.size.x / 2, position.position.y + size.size.y / 2 + 10};

        int width = spellCaster.currentCastDirections.size() * 12;

        for (int i = 0; i < spellCaster.currentCastDirections.size(); i++)
        {
            CastDirection direction = spellCaster.currentCastDirections[i];
            Texture texture = castDirectionToTexture(direction);

            raylib::Vector2 direction_position = raylib::Vector2{direction_center.x - width / 2 + i * 12, direction_center.y}; // TODO: remove magic numbers
        
            DrawTexture(texture, direction_position.x, direction_position.y, raylib::Color{255, 255, 255, 255});
        }

    }

}