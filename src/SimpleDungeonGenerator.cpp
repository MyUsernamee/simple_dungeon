#include "SimpleDungeonGenerator.hpp"

Dungeon SimpleDungeonGenerator::generateDungeon(int width, int height)
{
    
    

}

SimpleDungeonGenerator::SimpleDungeonGenerator()
{
    
    dungeon = Dungeon(16, 16, new int[16 * 16], tileSet);
    tileSet = TileSet("assets/Modern tiles_Free/Interiors_free/16x16/Interiors_free_16x16.png", 16);

}