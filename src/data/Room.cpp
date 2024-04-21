#include "data/Room.hpp"

Room::Room()
{

    this->tileSet = new TileSet();
    this->tiles = new int[ROOM_WIDTH * ROOM_HEIGHT];
    for (int i = 0; i < ROOM_WIDTH * ROOM_HEIGHT; i++) {
        this->tiles[i] = -1;
    }
    this->width = ROOM_WIDTH;
    this->height = ROOM_HEIGHT;

}

Room::Room(int* tiles, TileSet* tileSet, int width, int height)
{

    this->tiles = tiles;
    this->tileSet = tileSet;
    this->width = width;
    this->height = height;

}

Room::Room(const char *filename)
{

    this->load(filename);

}

Room::~Room()
{

    //delete[] this->tiles;

}

void Room::load(const char* filename)
{

    FILE* file = fopen(filename, "rb");
    fread(&this->width, sizeof(int), 1, file);
    fread(&this->height, sizeof(int), 1, file);
    this->tiles = new int[this->width * this->height];
    fread(this->tiles, sizeof(int), this->width * this->height, file);

    fclose(file);

}

void Room::save(const char* filename)
{

    FILE* file = fopen(filename, "wb");
    fwrite(&this->width, sizeof(int), 1, file);
    fwrite(&this->height, sizeof(int), 1, file);
    fwrite(this->tiles, sizeof(int), this->width * this->height, file);

    fclose(file);

}

void Room::place(int x, int y, int* newTiles, int newWidth, int newHeight)
{

    for (int i = 0; i < newWidth; i++) {
        for (int j = 0; j < newHeight; j++) {
            if (i + x >= 0 && i + x < newWidth && j + y >= 0 && j + y < newHeight &&
                i >= 0 && i < this->width && j >= 0 && j < this->height && tiles[j * this->width + i] != -1) {
                newTiles[(j + y) * newWidth + (i + x)] = this->tiles[j * this->width + i];
            }
        }
    }

}