#include "utils/TileSet.hpp"
#include "Components.hpp"
#include "tmxlite/Tileset.hpp"

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
        void render(raylib::Camera2D camera);

        // Renders a lighting texture
        void renderLighting(raylib::Camera2D camera, std::vector<std::pair<raylib::Vector2, Light>> visiblity_points);

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

        Tile getTile(int x, int y) {

            return tileSet.getTile(tiles[x + y * width]);

        }

        bool rayCast(raylib::Vector2 start, raylib::Vector2 end, float* outDistance = nullptr);
        std::vector<raylib::Vector2> pathFind(raylib::Vector2 start, raylib::Vector2 end);
        // TODO: Make a better pathfinding system.

        int width;
        int height;
        int* tiles;
        double* opacity;
        TileSet tileSet;

};