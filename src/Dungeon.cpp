#include "Dungeon.hpp"

Dungeon::Dungeon(int width, int height, int *tiles, TileSet tileSet)
{

    this->width = width;
    this->height = height;
    this->tiles = tiles;
    this->tileSet = tileSet;

}

Dungeon::Dungeon()
{

    width = 0;
    height = 0;
    tiles = nullptr;
    tileSet = TileSet();

}

Dungeon::~Dungeon()
{

    //delete[] tiles;

}

void Dungeon::render(raylib::Camera2D camera)
{

    int start_x = ((int)camera.target.x - (int)camera.offset.x) / TILE_SIZE;
    int start_y = ((int)camera.target.y - (int)camera.offset.y) / TILE_SIZE;

    int end_x = start_x + GetRenderWidth() / TILE_SIZE + 1;
    int end_y = start_y + GetRenderHeight() / TILE_SIZE + 2;
    
    for (int y = start_y; y < end_y; y++) {

        for (int x = start_x; x < end_x; x++) {

            if (tiles[y * width + x] == -1) continue;
            if (x < 0 || x >= width || y < 0 || y >= height) continue; // TODO: Make this use a clamp function instead of if statements

            Tile tile = tileSet.getTile(tiles[y * width + x]);

            DrawTextureEx(tile.texture, {(float)x * TILE_SIZE, (float)y * TILE_SIZE}, 0, TILE_SIZE / tile.texture.width, WHITE);

        }

    }

}