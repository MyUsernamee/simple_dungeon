#include <raylib-cpp.hpp>
#include "TileSet.hpp"

int main () {

    raylib::Window w(800, 450, "Hello, World!");

    TileSet testTileSet("assets/0x72_DungeonTilesetII_v1.7/0x72_DungeonTilesetII_v1.7.png", 16);

    while (!w.ShouldClose()) {

        w.BeginDrawing();
        w.ClearBackground(RAYWHITE);
        
        // We are going to draw every tile for testing
        for (int i = 0; i < 16; i++) {
            DrawTexture(testTileSet.getTile(i).texture, i * 16, 0, WHITE);
        }


        w.EndDrawing();


    }

    return 0;
    
}