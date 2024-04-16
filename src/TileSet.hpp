#include <raylib-cpp.hpp>

/**
 * @brief Basic class for a tile set.
 * Contains the textures and basic data about each tile.
 * 
*/
class TileSet {

    struct Tile {

        raylib::Texture texture;
        bool solid;

    };

    public:

        TileSet();
        ~TileSet();

        /**
         * @brief Add a tile to the tile set.
        */
        void addTile(raylib::Texture texture, bool solid);

        /**
         * @brief Get a tile from the tile set.
        */
        Tile getTile(int index);

    private:

        std::vector<Tile> tiles;


};