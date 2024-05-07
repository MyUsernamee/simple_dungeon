
#include "Game.hpp"
#include <utils/consts.hpp>

void statsRenderer(Game* game, double dt) 
{

    auto& registry = game->getRegistry();

    auto view = registry.view<Player, Health, SpellCaster, Renderable>();
    int offset = 128;

    int box_width = GetRenderWidth() / 4;
    int box_height = 128;
    int top_padding = 10; // Define the top padding value
    for (auto entity : view) {
                
        auto& player = view.get<Player>(entity);
        auto& health = view.get<Health>(entity);
        auto& mana = view.get<SpellCaster>(entity);
        auto& renderable = view.get<Renderable>(entity);

        double health_percentage = (double)health.health / (double)health.maxHealth;
        double mana_percentage = mana.mana / mana.maxMana;
        // TODO: Blood Percentage

        // Draw a bubble around the player icon
        DrawCircle(offset + box_height / 2, box_height / 2, box_height / 2, BLACK); // TODO: Replace with color map
        float square_size = box_height * (0.7071);
        DrawTexturePro
        (
            renderable.texture,
            Rectangle{0, 0, (float)renderable.texture.width, (float)renderable.texture.height},
            Rectangle{(float)offset + (box_height - square_size) / 2, (float)(box_height - square_size) / 2,  (float)square_size, (float)square_size},
            Vector2{0, 0},
            0,
            renderable.color
        );
        DrawRing
        (
            Vector2{(float)offset + box_height / 2, (float)box_height / 2},
            box_height / 2,
            box_height / 2 + 4,
            0,
            180 * health_percentage,
            64,
            RED
        );
        DrawRing
        (
            Vector2{(float)offset + box_height / 2, (float)box_height / 2},
            box_height / 2 + 4,
            box_height / 2 + 8,
            0,
            180 * mana_percentage,
            64,
            BLUE
        );
        


        offset += box_width * 1.2;

    }

}