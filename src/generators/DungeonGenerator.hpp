
#include <raylib-cpp.hpp>
#include "data/Dungeon.hpp"

/**
 * 
 * @brief Abstract class for generating dungeons.
 * 
*/
class DungeonGenerator {

    public:

        virtual Dungeon generateDungeon(int width, int height) = 0;

};