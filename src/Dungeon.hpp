#include "TileSet.hpp"

#pragma once

const int TILE_SIZE = 32;

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
        void render(raylib::Camera2D camera); // Camera used for Optimization so we don't render tiles that are not visible.

        // TOOD: Add getters and setters for everything.
        TileSet getTileSet() {
            return tileSet;
        }

        int getWidth() {
            return width;
        }
        int getHeight() {
            return height;
        }
        int* getTiles() {
            return tiles;
        }

        Tile& getTile(int x, int y) {

            return tileSet.getTile(tiles[y * width + x]);
        }

    

        int width;
        int height;
        int* tiles;
        TileSet tileSet;

};