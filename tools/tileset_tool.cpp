
#include <raylib-cpp.hpp>
#include <raygui.h>
#include <rlgl.h>
#include "TileSet.hpp"

#define ROOM_WIDTH 32
#define ROOM_HEIGHT 32
#define TILE_SIZE 16

int main(int argc, char* argv[]) {

    TileSet tileSet = TileSet();

    // Load all of the tiles
    // for (int i = 1; i < argc; i++) {
    //     tileSet.load(argv[i], TILE_SIZE);
    // }

    // For testing we load a predefined tileset

    raylib::Window w(800, 450, "Hello, World!");
    SetTargetFPS(60);
    if (FileExists("tileset.tit")) {
        tileSet.loadbin("tileset.tit", TILE_SIZE);
    } else {
        tileSet.load("assets/0x72_DungeonTilesetII_v1.7/atlas_floor-16x16.png", TILE_SIZE);
    }

    raylib::Camera2D camera({GetRenderWidth() / 2, GetRenderHeight() / 2}, {GetRenderWidth() / 2, GetRenderHeight() / 2}, 0.0f, 1.0f);

    int selectedTile = 0;

    int* tiles = new int[ROOM_WIDTH * ROOM_HEIGHT];

    while (!w.ShouldClose()) {
        
        BeginDrawing();
        ClearBackground(RAYWHITE);



        camera.BeginMode();

        // Draw a grid
        for (int x = 0; x < ROOM_WIDTH; x++) {
            for (int y = 0; y < ROOM_HEIGHT; y++) {
                Rectangle rect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
                DrawRectangleLinesEx(rect, 1, DARKGRAY);

                // Draw the tiles
                int currentTileIndex = tiles[x + y* ROOM_WIDTH];
                Tile tile = tileSet.getTile(currentTileIndex);
                
                DrawTexture(
                
            }
        }

        // Camera controls
        if (IsKeyDown(KEY_W)) camera.target.y -= 10;
        if (IsKeyDown(KEY_S)) camera.target.y += 10;
        if (IsKeyDown(KEY_A)) camera.target.x -= 10;
        if (IsKeyDown(KEY_D)) camera.target.x += 10;
        if (GetMouseWheelMove() > 0) camera.zoom += 0.1f;
        if (GetMouseWheelMove() < 0) camera.zoom -= 0.1f;
        if (IsKeyPressed(KEY_LEFT)) selectedTile -= 1;
        if (IsKeyPressed(KEY_RIGHT)) selectedTile += 1;
        if (IsKeyPressed(KEY_SPACE)) tileSet.getTile(selectedTile).solid = !tileSet.getTile(selectedTile).solid;

        selectedTile = Clamp(selectedTile, 0, tileSet.getTileCount() - 1);

        camera.EndMode();



        // Draw the selected tile
        Rectangle selectedTileRect = { 10, 10, TILE_SIZE, TILE_SIZE };
        DrawTextureEx(tileSet.getTile(selectedTile).texture, {10, 10}, 0, 1, WHITE);
        DrawRectangleLinesEx(selectedTileRect, 1, BLACK);

        DrawText(TextFormat("Selected Tile: %i", selectedTile), 10, 30, 20, BLACK);
        DrawText(TextFormat("Solid: %s", tileSet.getTile(selectedTile).solid ? "true" : "false"), 10, 50, 20, BLACK);

        

        EndDrawing();
    }

    tileSet.savebin("tileset.tit", TILE_SIZE);

    return 0;

}