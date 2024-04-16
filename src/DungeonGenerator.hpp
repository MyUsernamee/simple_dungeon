
#include <raylib-cpp.hpp>

/**
 * 
 * @brief Abstract class for generating dungeons.
 * 
*/
class DunegonGenerator {

    public:

        virtual Dungeon generateDungeon(int width, int height) = 0;

};