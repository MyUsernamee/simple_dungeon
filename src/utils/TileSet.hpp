#include <raylib-cpp.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/map.hpp>
#include <map>
#include <nlohmann/json.hpp>

#pragma once

/**
 * @brief Basic struct for a tile.
*/
struct Tile {

    std::vector<Texture2D> textures = {};
    std::map<std::string, std::string> properties = {}; // Properties of the tile.
    // Why a map of strings instead of just adding the properties to the struct?
    // This way, we can add properties to the tile without changing the struct.
    // As such when we want to add new properties to the tile, we don't need to remake all of our tilesets.
    // We can just add the new properties to the map.
    // This does cause a slight performance hit, but it is worth it for the flexibility.

    template <class Archive>
    void serialize(Archive & archive)
    {
        
        archive(
            CEREAL_NVP(textures),
            CEREAL_NVP(properties)
        );
    }

    bool getBoolProperty(std::string key) {
        if (properties.find(key) == properties.end()) {
            return false;
        }
        return properties[key] == "true";
    }
    int getIntProperty(std::string key) {
        if (properties.find(key) == properties.end()) {
            return 0;
        }
        return std::stoi(properties[key]);
    }
    std::string getStringProperty(std::string key) {
        if (properties.find(key) == properties.end()) {
            return "";
        }
        return properties[key];
    }
    float getFloatProperty(std::string key) {
        if (properties.find(key) == properties.end()) {
            return 0.0f;
        }
        return std::stof(properties[key]);
    }

    bool hasProperty(std::string key) {
        return properties.find(key) != properties.end();
    }

    void loadFromJson(nlohmann::json j) {
        for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it) {
            if (it.key() == "textures") {
                for (nlohmann::json::iterator it2 = it.value().begin(); it2 != it.value().end(); ++it2) {
                    textures.push_back(LoadTexture(it2.value().get<std::string>().c_str()));
                }
            } else {
                properties[it.key()] = it.value().get<std::string>();
            }
        }
    }

};

template <class Archive>
void save(Archive & archive, const Texture2D & texture) 
{
    int fileSize = 0;
    char* data_buffer = (char*)ExportImageToMemory(LoadImageFromTexture(texture), ".png", &fileSize);
    
    // We need to read in the data according to file size because the data may contain null characters.
    std::string data(data_buffer, fileSize);
    
    archive(CEREAL_NVP(data));
}

template <class Archive>
void load(Archive & archive, Texture2D & texture) 
{
    std::string data;
    archive(CEREAL_NVP(data));

    // If the data doesn't start with the PNG header, it is a directory path.
    if (data.find("PNG") != 1) {
        texture = LoadTexture(data.c_str());
        return;
    }

    const unsigned char* textureDataConst = reinterpret_cast<const unsigned char*>(data.c_str());
    Image image = LoadImageFromMemory(".png", textureDataConst, data.size());
    texture = LoadTextureFromImage(image);
}

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
        TileSet(char* path); // Load a tileset from a file.
        ~TileSet();

        /**
         * @brief Load a tileset from a file.
        */
        void load(char* path);
        /**
         * @brief Save a tileset to a file.
        */
        void save(char* path);

        /**
         * @brief Load a tileset from a json file.
        */
        void loadFromJson(char* path);

        /**
         * @brief Add a tile to the tile set.
        */
        void addTile(Tile tile);

        /**
         * @brief Get a tile from the tile set.
        */
        Tile getTile(int index);

        /**
         * @brief Get the number of tiles in the tile set.
        */
        int getTileCount() { return tiles.size(); }

        /**
         * @brief Get tiles
        */
        std::vector<Tile>& getTiles() { return tiles; }

        template <class Archive>
        void serialize(Archive & archive)
        {
            archive(
                CEREAL_NVP(tiles)
            );
        }

    private:

        std::vector<Tile> tiles;


};