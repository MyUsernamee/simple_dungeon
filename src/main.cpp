#include <raylib-cpp.hpp>
#include "Game.hpp"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"


#define DEBUG // Comment this line to remove debug information.
#define DEBUG_PADDING 10

int main () {

    raylib::Window w(800, 450, "Hello, World!");
    

    SetTargetFPS(60);

    Game game = Game();

    while (!w.ShouldClose()) {

        w.BeginDrawing();
        w.ClearBackground(RAYWHITE);


        game.run();

        w.EndDrawing();

        #ifdef DEBUG
        DrawText("This is a debug build", DEBUG_PADDING, w.GetHeight() - DEBUG_PADDING - 10, 10, DARKGRAY);
        DrawFPS(10, 10);
        
        Rectangle window_rect = (Rectangle){ w.GetWidth() - 200 - DEBUG_PADDING, DEBUG_PADDING, 200, w.GetHeight() - 2 * DEBUG_PADDING };
        GuiWindowBox(window_rect, "Debug Information");

        // We are going 


        #endif

    }

    return 0;
    
}