
#include <raylib-cpp.hpp>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <rlgl.h>
#include "utils/TileSet.hpp"
#include <data/Room.hpp>

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

    raylib::Window w(1280, 720, "Tileset Tool");
    SetTargetFPS(60);
    if (FileExists("tileset.tileset")) {
        tileSet.loadbin("tileset.tileset", TILE_SIZE);
        TraceLog(LOG_INFO, "Loaded tileset from file");
    } else {
        tileSet.load("assets/0x72_DungeonTilesetII_v1.7/atlas_floor-16x16.png", TILE_SIZE);
        tileSet.load("assets/0x72_DungeonTilesetII_v1.7/atlas_walls_high-16x32.png", TILE_SIZE);
    }

    raylib::Camera2D camera({GetRenderWidth() / 2, GetRenderHeight() / 2}, {GetRenderWidth() / 2, GetRenderHeight() / 2}, 0.0f, 1.0f);

    int selectedTile = 0;

    int* tiles = new int[ROOM_WIDTH * ROOM_HEIGHT];
    for (int i = 0; i < ROOM_WIDTH * ROOM_HEIGHT; i++) {
        tiles[i] = -1;
    }

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
                int currentTileIndex = tiles[x + y * ROOM_WIDTH];

                if (currentTileIndex == -1) continue;
                Tile tile = tileSet.getTile(currentTileIndex);
                
                DrawTexture(tile.texture, x * TILE_SIZE, y * TILE_SIZE, WHITE);
                
            }
        }

        // Render a dot for the center of the room
        DrawCircle(ROOM_WIDTH * TILE_SIZE / 2, ROOM_HEIGHT * TILE_SIZE / 2, 5, RED);

        // Camera controls
        if (IsKeyDown(KEY_W)) camera.target.y -= 10;
        if (IsKeyDown(KEY_S)) camera.target.y += 10;
        if (IsKeyDown(KEY_A)) camera.target.x -= 10;
        if (IsKeyDown(KEY_D)) camera.target.x += 10;
        if (GetMouseWheelMove() > 0) camera.zoom += 0.1f;
        if (GetMouseWheelMove() < 0) camera.zoom -= 0.1f;
        if (IsKeyPressed(KEY_SPACE)) tileSet.getTile(selectedTile).solid = !tileSet.getTile(selectedTile).solid;
        if (IsKeyPressed(KEY_R)) selectedTile = -1;

        if (IsKeyDown(KEY_LEFT_CONTROL)) {
            if (IsKeyPressed(KEY_S)) {
                tileSet.savebin("tileset.tileset", TILE_SIZE);

                // Create a room from the tiles
                Room room(tiles, &tileSet, ROOM_WIDTH, ROOM_HEIGHT);
                room.save("room.room");

            }

        }

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = camera.GetScreenToWorld(GetMousePosition());
            int x = (int)mousePos.x / TILE_SIZE;
            int y = (int)mousePos.y / TILE_SIZE;
            if (x >= 0 && x < ROOM_WIDTH && y >= 0 && y < ROOM_HEIGHT)
            tiles[x + y * ROOM_WIDTH] = selectedTile;
        }

        selectedTile = Clamp(selectedTile, -1, tileSet.getTileCount() - 1);

        camera.EndMode();



        // Draw the selected tile
        if (selectedTile != -1) {
            Rectangle selectedTileRect = { 10, 10, TILE_SIZE, TILE_SIZE };
            DrawTextureEx(tileSet.getTile(selectedTile).texture, {10, 10}, 0, 1, WHITE);
            DrawRectangleLinesEx(selectedTileRect, 1, BLACK);

            DrawText(TextFormat("Selected Tile: %i", selectedTile), 10, 30, 20, BLACK);
            DrawText(TextFormat("Solid: %s", tileSet.getTile(selectedTile).solid ? "true" : "false"), 10, 50, 20, BLACK);
        }

        if (IsKeyDown(KEY_TAB)) {
            
            int height_tiles = tileSet.getTileCount() / 16;
            int width_tiles = 16;
            GuiWindowBox(raylib::Rectangle(10, 70, TILE_SIZE * 16, TILE_SIZE * height_tiles), "Tileset");
            
            // Draw the tileset
            for (int i = 0; i < tileSet.getTileCount(); i++) {
                int x = i % width_tiles;
                int y = i / width_tiles;
                Rectangle tileRect = { x * TILE_SIZE + 10, y * TILE_SIZE + 70, TILE_SIZE, TILE_SIZE };
                DrawTextureEx(tileSet.getTile(i).texture, {(float)x * TILE_SIZE + 10, (float)y * TILE_SIZE + 70}, 0, 1, WHITE);
                DrawRectangleLinesEx(tileRect, 1, BLACK);
                if (CheckCollisionPointRec(GetMousePosition(), tileRect) && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                    selectedTile = i;
                }
            }

        }

        EndDrawing();
    }

    tileSet.savebin("tileset.tileset", TILE_SIZE);

    return 0;

}