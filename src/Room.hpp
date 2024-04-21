#pragma once

#include <raylib-cpp.hpp>
#include "TileSet.hpp"

const int ROOM_WIDTH = 32;
const int ROOM_HEIGHT = 32;

/**
 * @brief Basic class for a room.
 * 
*/
class Room {

    public:

        Room();
        Room(int* tiles, TileSet* tileSet, int width, int height);
        Room(const char* filename);
        ~Room();

        /**
         * @brief Load a room from .bin file.
        */
        void load(const char* filename);
        /**
         * @brief Save a room to .bin file.
        */
        void save(const char* filename);
        /**
         * @brief Place the room at a specific position. in a bigger map.
        */
        void place(int x, int y, int* newTiles, int newWidth, int newHeight);

        int getWidth() { return width; }
        int getHeight() { return height; }

    private:

        TileSet* tileSet;
        int* tiles;
        int width;
        int height;

};