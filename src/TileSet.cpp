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

            raylib::Texture tileTexture = tileImage.LoadTexture();

            addTile(&tileTexture, false);

        }

    }

}

void TileSet::addTile(raylib::Texture* texture, bool solid)
{

    Tile tile;
    tile.texture = texture;
    tile.solid = solid;

    tiles.push_back(tile);

}
