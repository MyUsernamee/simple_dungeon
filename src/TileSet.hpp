#include <raylib-cpp.hpp>

#pragma once

/**
 * @brief Basic struct for a tile.
*/
struct Tile {

    Texture2D texture;
    bool solid;

};

/**
 * @brief Basic class for a tile set.
 * Contains the textures and basic data about each tile.
 * 
*/
class TileSet {

    public:

        TileSet();
        /**
         * @brief Load a tileset from a file.
         * @param path The path to the texture atlas file.
         * @param size The width and height of each tile.
        */
        TileSet(char* path, int size); // Load a tileset from a file.
        ~TileSet();

        /**
         * @brief Load a tileset from a file.
         * @param path The path to the texture atlas file.
         * @param size The width and height of each tile.
         * @note This function is called by the constructor, it adds the tiles to the tile set.
        */
        void load(char* path, int size);
        // Load a tileset from a file.
        void loadbin(char* path, int size);
        // Save a tileset to a file.
        void savebin(char* path, int size);

        /**
         * @brief Add a tile to the tile set.
        */
        void addTile(Texture2D texture, bool solid);

        /**
         * @brief Get a tile from the tile set.
        */
        Tile& getTile(int index);

        /**
         * @brief Get the number of tiles in the tile set.
        */
        int getTileCount() { return tiles.size(); }

        /**
         * @brief Get tiles
        */
        std::vector<Tile> getTiles() { return tiles; }

    private:

        std::vector<Tile> tiles;
        Tile EMPTY_TILE {
            .texture = {},
            .solid = true
        };


};