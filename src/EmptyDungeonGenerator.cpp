#include "EmptyDungeonGenerator.hpp"

EmptyDungeonGenerator::EmptyDungeonGenerator() {

    tileSet = TileSet("assets/0x72_DungeonTilesetII_v1.7/atlas_floor-16x16.png", 16);
    tileSet.load("assets/0x72_DungeonTilesetII_v1.7/atlas_walls_high-16x32.png", 16);

    // Make Tile 1 solid
    tileSet.getTile(1).solid = true;

}

Dungeon EmptyDungeonGenerator::generateDungeon(int width, int height) {
    
    // Walls are solid
    int* tiles = new int[width * height];

    for (int i = 0; i < width * height; i++) {
        tiles[i] = 0; // Floor
    }

    // Top and bottom walls
    for (int x = 0; x < width; x++) {
        tiles[x] = 1;
        tiles[(height - 1) * width + x] = 1;
    }

    // Left and right walls
    for (int y = 0; y < height; y++) {
        tiles[y * width] = 1;
        tiles[y * width + width - 1] = 1;
    }

    return Dungeon(width, height, tiles, tileSet);

}