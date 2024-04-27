
#include "Game.hpp"
#include <utils/consts.hpp>

void statsRenderer(Game* game, double dt) 
{

    auto& registry = game->getRegistry();

    auto view = registry.view<Player, Health, Renderable>();
    int offset = 0;

    int box_width = GetRenderWidth() / 4;

    for (auto entity : view) {
        

        auto& player = view.get<Player>(entity);
        auto& health = view.get<Health>(entity);
        auto& renderable = view.get<Renderable>(entity);

        DrawRectangle(offset * box_width, 0, box_width, 100, RED);
        DrawText(std::to_string(health.health).c_str(), offset * box_width + 10, 10, 20, WHITE);
        DrawText("Health", offset * box_width + 10, 40, 20, WHITE);

        DrawTexture(renderable.texture, offset * box_width + 10, 60, renderable.color);

        offset++;

    }

}