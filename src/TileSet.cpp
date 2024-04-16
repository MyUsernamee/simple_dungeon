#include "TileSet.hpp"
#include <vector>

TileSet::TileSet()
{

    tiles = std::vector<Tile>();

}

TileSet::TileSet(char * path, int size)
{

    tiles = std::vector<Tile>();

    int width, height;

    raylib::Image texture = raylib::LoadImage(path);

    width = texture.GetWidth() / size;
    height = texture.GetHeight() / size;

    for (int y = 0; y < height; y++) {

        for (int x = 0; x < width; x++) {

            raylib::Rectangle source = raylib::Rectangle(x * size, y * size, size, size);
            raylib::Image tileImage = texture.Copy();
            tileImage.Crop(source);



            addTile(tileImage.LoadTexture(), false);

        }

    }

}

TileSet::~TileSet()
{

    // Do nothing.

}

void TileSet::addTile(Texture2D texture, bool solid)
{

    Tile tile;
    tile.texture = texture;
    tile.solid = solid;

    tiles.push_back(tile);

}

Tile& TileSet::getTile(int index)
{
    
    return tiles[index];
}
