
#include "SimpleDungeonGenerator.hpp"

Dungeon generateDungeon(int width, int height) {
    Dungeon dungeon(width, height);
    Room room(0, 0, width, height);
    dungeon.addRoom(room);
    return dungeon;
}