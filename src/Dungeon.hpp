#include "TileSet.hpp"

#pragma once

/**
 * @brief Basic class for a dungeon.
 * 
*/
class Dungeon {

    public:

        Dungeon(int width, int height, int* tiles, TileSet tileSet);
        Dungeon();
        ~Dungeon();

        /**
         * @brief Render the dungeon.
        */
        void render();

        // TOOD: Add getters and setters for everything.

    

        int width;
        int height;
        int* tiles;
        TileSet tileSet;

};