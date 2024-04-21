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
        void render(raylib::Camera2D camera, std::vector<raylib::Vector2> visiblity_points);

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

            if (x < 0 || x >= width || y < 0 || y >= height) {
                return EMPTY_TILE;
            }

            if (tiles[y * width + x] == -1) {
                return EMPTY_TILE;
            }

            return tileSet.getTile(tiles[y * width + x]);
        }

        bool rayCast(raylib::Vector2 start, raylib::Vector2 end, float* outDistance = nullptr);
        std::vector<raylib::Vector2> pathFind(raylib::Vector2 start, raylib::Vector2 end);

        int width;
        int height;
        int* tiles;
        double* opacity;
        TileSet tileSet;
        Tile EMPTY_TILE {
            .texture = {},
            .solid = true
        };

};