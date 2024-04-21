#include "TileSet.hpp"
#include <vector>

TileSet::TileSet()
{

    tiles = std::vector<Tile>();

}

TileSet::TileSet(char * path, int size)
{

    tiles = std::vector<Tile>();

    load(path, size);

}

void TileSet::load(char * path, int size)
{

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

void TileSet::loadbin(char *path, int size)
{

    // Load the file
    FILE *file = fopen(path, "rb");

    if (file == NULL) {

        TraceLog(LOG_ERROR, "Failed to open file %s", path);
        return;

    }

    // Read the number of tiles
    int tileCount;
    fread(&tileCount, sizeof(int), 1, file);

    // Read the tiles
    for (int i = 0; i < tileCount; i++) {

        // Read the texture
        int textureSize;
        fread(&textureSize, sizeof(int), 1, file);

        char *textureData = new char[textureSize];
        fread(textureData, sizeof(char), textureSize, file);

        Image image = LoadImageFromMemory(".png", (unsigned char *)textureData, textureSize);
        Texture2D texture = LoadTextureFromImage(image);

        // Read the solid flag
        bool solid;
        fread(&solid, sizeof(bool), 1, file);

        // Add the tile
        addTile(texture, solid);

        // Clean up
        delete[] textureData;

    }

}

void TileSet::savebin(char *path, int size)
{

    // Open the file
    FILE *file = fopen(path, "wb");

    if (file == NULL) {

        TraceLog(LOG_ERROR, "Failed to open file %s", path);
        return;

    }

    // Write the number of tiles
    int tileCount = tiles.size();
    fwrite(&tileCount, sizeof(int), 1, file);

    // Write the tiles
    for (int i = 0; i < tileCount; i++) {

        // Write the texture
        // Convert Texture to TextureUnmanaged
        raylib::TextureUnmanaged texture = tiles[i].texture;
        raylib::Image image = texture.GetData();
        int textureSize;
        unsigned char *textureData = ExportImageToMemory(image, ".png", &textureSize);

        

        fwrite(&textureSize, sizeof(int), 1, file);
        fwrite(textureData, sizeof(char), textureSize, file);

        // Write the solid flag
        fwrite(&tiles[i].solid, sizeof(bool), 1, file);

        // Clean up
        
        delete[] textureData;

    }

    // Close the file
    fclose(file);

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
