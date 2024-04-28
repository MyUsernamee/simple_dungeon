
#include <raylib-cpp.hpp>
#include "Game.hpp"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "Components.hpp"
#include "Systems.hpp"
#include "renderers/stats_renderer.hpp"
#include "generators/SimpleDungeonGenerator.hpp"

int main () {

    raylib::Window w(GetScreenWidth(), GetScreenHeight(), "Dungeon Generator");
    
    w.SetFullscreen(true);

    SetTargetFPS(GetMonitorRefreshRate(0));
    SetWindowMonitor(0);


    Game game = Game();
    game.setSystems(getSystems());
    game.registerRenderSystem(statsRenderer);

    generateDungeon(&game, 512, 512);

    while (!w.ShouldClose()) {

        w.BeginDrawing();
        w.ClearBackground(BLACK);

        game.run();

        w.EndDrawing();

    }

    return 0;
    
}