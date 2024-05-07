

#include <tmxlite/Tileset.hpp>
#include <tmxlite/Property.hpp>
#include <vector>
#include <map>
#include <raylib.h>
#include <string>

// Acts as a wrapper over the basic tmx tile that allows for the tile to function with raylib.

/**
 * @brief Basic struct for a tile.
*/
class RaylibTile: public tmx::Tileset::Tile {

    public:

        std::vector<Texture2D> textures = {};
        std::map<std::string, tmx::Property> properties_map = {};

        RaylibTile() {
        }

        RaylibTile(const tmx::Tileset::Tile& tile) {
            
        }

};
