#include "SimpleDungeonGenerator.hpp"
#define JC_VORONOI_IMPLEMENTATION
#include "jc_voronoi.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Dungeon SimpleDungeonGenerator::generateDungeon(int width, int height)
{
    
    dungeon = Dungeon(width, height, new int[width * height], tileSet);
    
    for (int y = 0; y < height; y++) {
        
        for (int x = 0; x < width; x++) {
            
            dungeon.tiles[y * width + x] = -1; // -1 is a placeholder for an empty tile.
            
        }
        
    }

    createRooms(16, 16, 32); // Create 10 rooms with a minimum size of 3 and a maximum size of 6.
    // wiggleRooms(); // Wiggle the rooms around so they are eqo-distant.
    createCorridors();
    // connectCorridorRooms(); // Connect the rooms with corridors.
    // removeDeadEnds(); // Remove dead ends.

    
    return dungeon;

}

void relax_points(const jcv_diagram* diagram, jcv_point* points)
{
    const jcv_site* sites = jcv_diagram_get_sites(diagram);
    for( int i = 0; i < diagram->numsites; ++i )
    {
        const jcv_site* site = &sites[i];
        jcv_point sum = site->p;
        int count = 1;

        const jcv_graphedge* edge = site->edges;

        while( edge )
        {
            sum.x += edge->pos[0].x;
            sum.y += edge->pos[0].y;
            ++count;
            edge = edge->next;
        }

        points[site->index].x = sum.x / count;
        points[site->index].y = sum.y / count;
    }
}

void SimpleDungeonGenerator::createRooms(int numberOfRooms, int minRoomSize, int maxRoomSize)
{

    //int i;
    jcv_rect boundingbox = { {0.0f, 0.0f}, { (float)dungeon.width * 16, (float)dungeon.height * 16 } };
    jcv_diagram diagram;
    jcv_point* points = new jcv_point[numberOfRooms];
    const jcv_site* sites = new jcv_site[numberOfRooms];
    jcv_graphedge* graphEdges;

    for (int i = 0; i < numberOfRooms; i++) {
        
        points[i].x = GetRandomValue(0, dungeon.width * 16);
        points[i].y = GetRandomValue(0, dungeon.height * 16);
        
    }

    memset(&diagram, 0, sizeof(jcv_diagram));

    jcv_diagram_generate(numberOfRooms, (const jcv_point*)points, &boundingbox, 0, &diagram);

    TraceLog(LOG_INFO, "Number of sites: %d", diagram.numsites);
    TraceLog(LOG_INFO, "Number of rooms: %d", numberOfRooms);
    
    relax_points(&diagram, points);

    const jcv_site* new_sites = jcv_diagram_get_sites(&diagram);

    raylib::Vector2* roomCenters = new raylib::Vector2[numberOfRooms];

    for (int i = 0; i < numberOfRooms; i++) {
        
        roomCenters[i] = raylib::Vector2(new_sites[i].p.x, new_sites[i].p.y);
        
    }

    jcv_diagram_free(&diagram);

    // Now we create the rooms.
    for (int i = 0; i < numberOfRooms; i++) {
        
        int x = roomCenters[i].x;
        int y = roomCenters[i].y;

        int roomWidth = GetRandomValue(minRoomSize, maxRoomSize);
        int roomHeight = GetRandomValue(minRoomSize, maxRoomSize);

        Room room = Room(x - roomWidth / 2, y - roomHeight / 2, roomWidth, roomHeight);
        
        room.fill(dungeon.tiles, 1, dungeon.width, dungeon.height);
        rooms.push_back(room);
        
    }

}

void SimpleDungeonGenerator::wiggleRooms()
{

    for(int i = 0; i < rooms.size(); i++) {
        
        Room room = rooms[i];
        
        raylib::Vector2 center = room.getCenter();

        // Get the 

        rooms[i] = room;
        
    }

}

SimpleDungeonGenerator::SimpleDungeonGenerator()
{
    
    
    tileSet = TileSet("assets/0x72_DungeonTilesetII_v1.7/atlas_floor-16x16.png", 16);
    tileSet.load("assets/0x72_DungeonTilesetII_v1.7/atlas_walls_high-16x32.png", 16);

}

SimpleDungeonGenerator::~SimpleDungeonGenerator()
{
    
    
    // Nothing to do here.
    
}

void SimpleDungeonGenerator::debugRender()
{
    
    // Draw our rooms.
    for (int i = 0; i < rooms.size(); i++) {
        
        Room room = rooms[i];
        
        room.getBounds().Draw(raylib::Color(255, 0, 0, 255));
        
    }

}

void SimpleDungeonGenerator::createCorridors()
{
    
    // Choose a random point
    // Choose a random point adjecent to the first point that doesn't have any neightbors.
    // That is now our new point.

}