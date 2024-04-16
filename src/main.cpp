#include <raylib-cpp.hpp>

int main () {

    raylib::Window w(800, 450, "Hello, World!");

    while (!w.ShouldClose()) {

        w.BeginDrawing();
        w.ClearBackground(RAYWHITE);
        DrawText("Hello, World!", 10, 10, 20, LIGHTGRAY);
        w.EndDrawing();


    }

    return 0;
    
}