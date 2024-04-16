#include "DungeonGenerator.hpp"
#include "Dungeon.hpp"
#include "TileSet.hpp"

#pragma once

/**
 * @brief Simple dungeon generator.
 * 
*/
class SimpleDungeonGenerator : public DungeonGenerator {

    public:

        SimpleDungeonGenerator();
        ~SimpleDungeonGenerator();

        /**
         * @brief Generate a dungeon.
        */
        Dungeon generateDungeon(int width, int height);

    private:

        Dungeon dungeon;
        TileSet tileSet;

};