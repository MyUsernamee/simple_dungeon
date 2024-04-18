#include "Room.hpp"



Room::Room()
{

    bounds = raylib::Rectangle(0, 0, 0, 0);

}

Room::Room(raylib::Rectangle bounds)
{

    this->bounds = bounds;

}

Room::Room(int x, int y, int width, int height)
{

    bounds = raylib::Rectangle(x, y, width, height);

}

Room::~Room()
{

}

void Room::fill(int *tiles, int tile, int width, int height)
{

    TraceLog(LOG_INFO, "Filling room with tile %d", tile);
    TraceLog(LOG_INFO, "Bounds: x: %f, y: %f, width: %f, height: %f", bounds.x, bounds.y, bounds.width, bounds.height);

    for (int y = bounds.y / 16; y < bounds.y / 16 + bounds.height / 16; y++) {

        for (int x = bounds.x / 16; x < bounds.x / 16 + bounds.width / 16; x++) {

            if (x < 0 || y < 0 || x >= width || y >= height) continue;

            int index = y * width + x;

            tiles[index] = tile;

        }

    }

}
