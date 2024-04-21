#include <raylib-cpp.hpp>
#include "Game.hpp"
#include "generators/EmptyDungeonGenerator.hpp"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "utils/AStar.hpp"
#include "Components.hpp"


// #define DEBUG // Comment this line to remove debug information.
#define DEBUG_PADDING 10

void aStarDemo() {

    // Construct a tile gird
    int* tiles = new int[20 * 20];
    for (int i = 0; i < 20 * 20; i++) {
        tiles[i] = 0;
    }

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("A* Pathfinding Algorithm", 10, 10, 20, DARKGRAY);

        // Draw a grid
        for (int x = 0; x < 20; x++) {
            for (int y = 0; y < 20; y++) {
                Rectangle rect = { x * 40, y * 40, 40, 40 };
                DrawRectangleLinesEx(rect, 1, DARKGRAY);
            }
        }

        // Draw the start and end points
        DrawRectangle(40 * 2, 40 * 2, 40, 40, GREEN);
        DrawRectangle(40 * 18, 40 * 18, 40, 40, RED);

        // Draw the grid
        for (int x = 0; x < 20; x++) {
            for (int y = 0; y < 20; y++) {
                if (tiles[y * 20 + x] == 1) {
                    DrawRectangle(x * 40, y * 40, 40, 40, GRAY);
                }
            }
        }

        // Where ever the user clicks
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            int x = GetMouseX() / 40;
            int y = GetMouseY() / 40;

            if (tiles[y * 20 + x] == 0) {
                tiles[y * 20 + x] = 1;
            }
            else {
                tiles[y * 20 + x] = 0;
            }
        }

        // Draw the path
        std::vector<raylib::Vector2> path = findPath(raylib::Vector2(2, 2), raylib::Vector2(18, 18), tiles, 20, 20);

        for (int i = 0; i < path.size(); i++) {
            DrawRectangle(path[i].x * 40, path[i].y * 40, 40, 40, BLUE);
        }

        EndDrawing();
    }

}

int main () {

    raylib::Window w(GetScreenWidth(), GetScreenHeight(), "Dungeon Generator");
    
    w.SetFullscreen(true);

    SetTargetFPS(60);

    EmptyDungeonGenerator generator = EmptyDungeonGenerator();
    Dungeon dungeon = generator.generateDungeon(256, 256);

    Game game = Game();

    game.setDungeon(dungeon);

    // aStarDemo();

    while (!w.ShouldClose()) {

        w.BeginDrawing();
        w.ClearBackground(BLACK);

        game.run();

        w.EndDrawing();

        #ifdef DEBUG
        DrawText("This is a debug build", DEBUG_PADDING, w.GetHeight() - DEBUG_PADDING - 10, 10, DARKGRAY);
        DrawFPS(10, 10);
        
        Rectangle window_rect = (Rectangle){ w.GetWidth() - 200 - DEBUG_PADDING, DEBUG_PADDING, 200, w.GetHeight() - 2 * DEBUG_PADDING };
        GuiWindowBox(window_rect, "Debug Information");

        // We are going display all entites and their components
        auto view = game.getRegistry().view<Position>();
        int y_offset = 20;

        for (auto entity : view) {
            auto &position = view.get<Position>(entity);
            DrawText(TextFormat("Entity: %i", entity), w.GetWidth() - 200 - DEBUG_PADDING + 10, DEBUG_PADDING + y_offset, 10, DARKGRAY);
            DrawText(TextFormat("Position: %f, %f", position.position.x, position.position.y), w.GetWidth() - 200 - DEBUG_PADDING + 10, DEBUG_PADDING + y_offset + 10, 10, DARKGRAY);
            y_offset += 20;
        }


        #endif

    }

    return 0;
    
}