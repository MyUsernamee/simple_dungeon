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

void Dungeon::render()
{

    for (int y = 0; y < height; y++) {

        for (int x = 0; x < width; x++) {

            if (tiles[y * width + x] == -1) continue;

            Tile tile = tileSet.getTile(tiles[y * width + x]);

            DrawTextureEx(tile.texture, {(float)x * TILE_SIZE, (float)y * TILE_SIZE}, 0, TILE_SIZE / tile.texture.width, WHITE);

        }

    }

}