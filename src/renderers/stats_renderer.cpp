
#include "Game.hpp"
#include <utils/consts.hpp>

void statsRenderer(Game* game, double dt) 
{

    auto& registry = game->getRegistry();

    auto view = registry.view<Player, Health, SpellCaster, Renderable>();
    int offset = 0;

    int box_width = GetRenderWidth() / 4;
    int box_height = 128;

    for (auto entity : view) {
        

        auto& player = view.get<Player>(entity);
        auto& health = view.get<Health>(entity);
        auto& mana = view.get<SpellCaster>(entity);
        auto& renderable = view.get<Renderable>(entity);

        // Draw a bubble around the player icon
        DrawCircleLines(offset + box_height / 2, box_height / 2, box_height / 2, GRAY); // TODO: Replace with color map
        DrawTexturePro
        (
            renderable.texture,
            Rectangle{0, 0, (float)renderable.texture.width, (float)renderable.texture.height},
            Rectangle{(float)offset + box_height / 4, (float)box_height / 4, (float)box_height / 2, (float)box_height / 2},
            Vector2{0, 0},
            0,
            renderable.color
        );
        


        offset++;

    }

}