#include <raylib-cpp.hpp>
#include "Game.hpp"

int main () {

    raylib::Window w(800, 450, "Hello, World!");

    while (!w.ShouldClose()) {

        w.BeginDrawing();
        w.ClearBackground(RAYWHITE);

        

        w.EndDrawing();


    }

    return 0;
    
}