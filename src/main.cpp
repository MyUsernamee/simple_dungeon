#include <raylib-cpp.hpp>
#include "Game.hpp"
#include "generators/EmptyDungeonGenerator.hpp"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "Components.hpp"
#include "Systems.hpp"

int main () {

    raylib::Window w(GetScreenWidth(), GetScreenHeight(), "Dungeon Generator");
    
    w.SetFullscreen(true);

    SetTargetFPS(GetMonitorRefreshRate(0));
    SetWindowMonitor(0);

    EmptyDungeonGenerator generator = EmptyDungeonGenerator();
    Dungeon dungeon = generator.generateDungeon(256, 256);

    Game game = Game();
    game.setSystems(getSystems());

    entt::entity dungeonEntity = game.getRegistry().create();
    game.getRegistry().emplace<Dungeon>(dungeonEntity, dungeon);
    

    while (!w.ShouldClose()) {

        w.BeginDrawing();
        w.ClearBackground(BLACK);

        game.run();

        w.EndDrawing();

    }

    return 0;
    
}