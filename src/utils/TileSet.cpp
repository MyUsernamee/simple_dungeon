#include "TileSet.hpp"
#include <vector>
#include "data/Dungeon.hpp"
#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include <fstream>
#include <nlohmann/json.hpp>

TileSet::TileSet()
{

    tiles = std::vector<Tile>();

}

TileSet::TileSet(char * path)
{

    tiles = std::vector<Tile>();

    load(path);

}

void TileSet::load(char * path)
{

    std::ifstream file (path);
    
    cereal::BinaryInputArchive archive(file);

    archive(tiles);

}

void TileSet::save(char * path)
{

    std::ofstream file (path);

    cereal::BinaryOutputArchive archive(file);

    archive(tiles);

}

void TileSet::loadFromJson(char * path)
{

    std::ifstream file (path);
    nlohmann::json j;
    file >> j;

    for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it) {
        Tile tile;
        tile.loadFromJson(it.value());
        tiles.push_back(tile);
    }

}

TileSet::~TileSet()
{

    // Do nothing.

}

void TileSet::addTile(Tile tile)
{

    tiles.push_back(tile);

}

Tile TileSet::getTile(int index)
{
    
    if (index < 0 || index >= tiles.size()) {
        return Tile();
    }

    return tiles[index];
}
