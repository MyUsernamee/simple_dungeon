#pragma once

#include <raylib-cpp.hpp>


/**
 * @brief Basic class for a room.
 * 
*/
class Room {

    public:

        Room();
        Room(raylib::Rectangle bounds);
        Room(int x, int y, int width, int height);
        ~Room();

        void fill(int* tiles, int tile, int width, int height); //

        raylib::Rectangle getBounds() { return bounds; }
        raylib::Vector2 getCenter() { return raylib::Vector2(bounds.x + bounds.width / 2, bounds.y + bounds.height / 2); }


    private:

        raylib::Rectangle bounds;

};