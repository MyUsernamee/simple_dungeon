#include <raylib-cpp.hpp>
#include "Game.hpp"
#include "EmptyDungeonGenerator.hpp"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"


#define DEBUG // Comment this line to remove debug information.
#define DEBUG_PADDING 10

int main () {

    raylib::Window w(GetScreenWidth(), GetScreenHeight(), "Dungeon Generator");
    
    w.SetFullscreen(true);

    SetTargetFPS(60);

    Game game = Game();

    EmptyDungeonGenerator generator = EmptyDungeonGenerator();
    Dungeon dungeon = generator.generateDungeon(128, 128);

    game.setDungeon(dungeon);

    while (!w.ShouldClose()) {

        w.BeginDrawing();
        w.ClearBackground(BLACK);

        // For testing lets display all of the TileSet
        for (int i = 0; i < dungeon.getTileSet().getTileCount(); i++) {
            DrawTexture(dungeon.getTileSet().getTile(i).texture, i * 16, 0, WHITE);

            // Display the index
            DrawText(std::to_string(i).c_str(), i * 16, 16, 10, WHITE);

        }

        game.run();

        w.EndDrawing();

        #ifdef DEBUG
        DrawText("This is a debug build", DEBUG_PADDING, w.GetHeight() - DEBUG_PADDING - 10, 10, DARKGRAY);
        DrawFPS(10, 10);
        
        Rectangle window_rect = (Rectangle){ w.GetWidth() - 200 - DEBUG_PADDING, DEBUG_PADDING, 200, w.GetHeight() - 2 * DEBUG_PADDING };
        GuiWindowBox(window_rect, "Debug Information");

        // We are going display all entites and their components
        // auto view = game.getRegistry()


        #endif

    }

    return 0;
    
}