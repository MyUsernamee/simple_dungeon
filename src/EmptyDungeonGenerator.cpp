#include "EmptyDungeonGenerator.hpp"
#include "overlapping_wfc.hpp"

EmptyDungeonGenerator::EmptyDungeonGenerator() {

    tileSet = TileSet("assets/0x72_DungeonTilesetII_v1.7/atlas_floor-16x16.png", 16);

    int floorCount = tileSet.getTileCount();

    tileSet.load("assets/0x72_DungeonTilesetII_v1.7/atlas_walls_high-16x32.png", 16);

    // Make every tile after the floor tiles solid
    for (int i = floorCount; i < tileSet.getTileCount(); i++) {
        tileSet.getTile(i).solid = true;
    }

}

Dungeon EmptyDungeonGenerator::generateDungeon(int width, int height) {
    
    // Walls are solid
    int* tiles = new int[width * height];
    // WE initialize everything with -1
    for (int i = 0; i < width * height; i++) {
        tiles[i] = -1;
    }

    // We load a sample dungeon image
    raylib::Image sample = raylib::LoadImage("assets/samples/sample.png");

    // We construct a array 2D
    Array2D<uint32_t> sampleArray = Array2D<uint32_t>(sample.width, sample.height);

    // We fill the array with the image data
    for (int y = 0; y < sample.height; y++) {
        for (int x = 0; x < sample.width; x++) {
            sampleArray.set(x, y, sample.GetColor(x, y).r);
        }
    }

    wfc::OverlappingWFC::Options options {

        true, // Periodic
        true, // Periodic output
        sample.width, sample.height,
        width, height,
        uint32_t((1 << 7) - 1), // 4 rotations
        3,
        wfc::Wave::Heuristic::Entropy,
        false

    };

    wfc::OverlappingWFC wfc = wfc::OverlappingWFC(options, sampleArray);

    wfc.run(rand());

    Array2D output = wfc.get_output();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            tiles[y * width + x] = (int)output.get(x, y)[2] - 1;
        }
    }

    return Dungeon(width, height, tiles, tileSet);

}