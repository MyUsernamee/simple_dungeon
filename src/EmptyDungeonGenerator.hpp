
#include "DungeonGenerator.hpp"
#include "Room.hpp"

#pragma once

class EmptyDungeonGenerator : public DungeonGenerator {
    
    public:
        EmptyDungeonGenerator();
        Dungeon generateDungeon(int width, int height) override;

    private:
        TileSet tileSet;
        std::vector<Room> room_templates;
    
};