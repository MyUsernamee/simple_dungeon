#include "DungeonGenerator.hpp"
#include "Dungeon.hpp"
#include "TileSet.hpp"
#include "Room.hpp"

#pragma once

/**
 * @brief Simple dungeon generator.
 * 
*/
class SimpleDungeonGenerator : public DungeonGenerator {

    public:

        SimpleDungeonGenerator();
        ~SimpleDungeonGenerator();

        /**
         * @brief Generate a dungeon.
        */
        Dungeon generateDungeon(int width, int height);

        /**
         * @brief Create rooms.
        */
        void createRooms(int numberOfRooms, int minRoomSize, int maxRoomSize);
        
        /**
         * @brief Render the dungeon.
        */
        void debugRender();
        
        void wiggleRooms(); // TODO: Remove this
        
        /**
         * @brief Create corridors.
         * Uses DFS to create corridors.
        */
        void createCorridors(); // TODO: Implment this.

    private:

        Dungeon dungeon;
        std::vector<Room> rooms;
        TileSet tileSet;

};