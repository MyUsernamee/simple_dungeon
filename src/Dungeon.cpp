#include "Dungeon.hpp"

Dungeon::Dungeon(int width, int height, int *tiles, TileSet tileSet)
{

    this->width = width;
    this->height = height;
    this->tiles = tiles;
    this->tileSet = tileSet;

}

Dungeon::~Dungeon()
{

    delete[] tiles;

}

void Dungeon::render()
{

    for (int y = 0; y < height; y++) {

        for (int x = 0; x < width; x++) {

            Tile tile = tileSet.getTile(tiles[y * width + x]);

            tile.texture->Draw(x * 16, y * 16);

        }

    }

}