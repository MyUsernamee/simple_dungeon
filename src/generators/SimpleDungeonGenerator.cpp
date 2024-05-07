
#include "SimpleDungeonGenerator.hpp"
#include "data/Dungeon.hpp"
#include <delaunator.hpp>
#include <entt/entt.hpp>
#include <queue>

#include "Game.hpp"

#include "utils/TileSet.hpp"
#include <utils/AStar.hpp>

#include <utils/utils.hpp>
#include <entities/DungeonSpider/constructor.hpp>
#include <entities/BloodAltar/constructor.hpp>
#include <entities/Candle/constructor.hpp>

const int HALLWAY_WIDTH = 4;

std::vector<std::pair<raylib::Vector2, raylib::Vector2>> generateDelaunayTriangulation(std::vector<raylib::Vector2> points) {
    std::vector<std::pair<raylib::Vector2, raylib::Vector2>> triangles;

    std::vector<double> coords;
    for (int i = 0; i < points.size(); i++) {
        coords.push_back(points[i].x);
        coords.push_back(points[i].y);
    }

    delaunator::Delaunator d(coords);

    for (std::size_t i = 0; i < d.triangles.size(); i += 3) {
        triangles.push_back(std::make_pair(raylib::Vector2(d.coords[2 * d.triangles[i]], d.coords[2 * d.triangles[i] + 1]), raylib::Vector2(d.coords[2 * d.triangles[i + 1]], d.coords[2 * d.triangles[i + 1] + 1])));
    }

    // De-deuplication
    for (int i = 0; i < triangles.size(); i++) {
        for (int j = i + 1; j < triangles.size(); j++) {
            if (triangles[i].first == triangles[j].first && triangles[i].second == triangles[j].second) {
                triangles.erase(triangles.begin() + j); // TODO: Use Set to de-duplicate.
                j--;
            }
        }
    }

    return triangles;
}


std::vector<std::pair<raylib::Vector2, raylib::Vector2>> generateMinimumSpanningTree(std::vector<std::pair<raylib::Vector2, raylib::Vector2>> triangles) {
    // Convert the input triangles to an undirected weighted graph
    std::set<std::pair<raylib::Vector2, raylib::Vector2>> edges;
    for (const auto& triangle : triangles) {
        edges.insert(triangle);
        edges.insert(std::make_pair(triangle.first, triangle.second));
        edges.insert(std::make_pair(triangle.second, triangle.first));
    }

    // Initialize the MST and the priority queue
    std::vector<std::pair<raylib::Vector2, raylib::Vector2>> mst;
    std::set<raylib::Vector2> visited;
    std::multiset<std::pair<float, std::pair<raylib::Vector2, raylib::Vector2>>> pq;

    // Start with the first vertex
    visited.insert(triangles[0].first);

    // Add all edges from the starting vertex to the priority queue
    for (const auto& edge : edges) {
        if (edge.first == triangles[0].first || edge.second == triangles[0].first) {
            float weight = Vector2Distance(edge.first, edge.second);
            pq.insert(std::make_pair(weight, edge));
        }
    }

    while (visited.size() < triangles.size() && !pq.empty()) {
        // Get the minimum weight edge
        auto [weight, edge] = *pq.begin();
        pq.erase(pq.begin());

        // If both vertices are not visited, add the edge to the MST
        if (visited.count(edge.first) == 0 || visited.count(edge.second) == 0) {
            mst.push_back(edge);
            visited.insert(edge.first);
            visited.insert(edge.second);

            // Add all edges from the newly visited vertex to the priority queue
            for (const auto& e : edges) {
                if (e.first == edge.first || e.first == edge.second || e.second == edge.first || e.second == edge.second) {
                    if (visited.count(e.first) != visited.count(e.second)) {
                        float weight = Vector2Distance(e.first, e.second);
                        pq.insert(std::make_pair(weight, e));
                    }
                }
            }
        }
    }

    return mst;
}

int* downscale(int* tiles, int width, int height, int scale) {
    int* new_tiles = new int[width / scale * height / scale];
    for (int x = 0; x < width / scale; x++) {
        for (int y = 0; y < height / scale; y++) {
            new_tiles[x + y * width / scale] = tiles[x * scale + y * scale * width];
        }
    }
    return new_tiles;
}

int* upscale(int* tiles, int width, int height, int scale) {
    int* new_tiles = new int[width * scale * height * scale];
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            for (int i = 0; i < scale; i++) {
                for (int j = 0; j < scale; j++) {
                    new_tiles[x * scale + i + (y * scale + j) * width * scale] = tiles[x + y * width];
                }
            }
        }
    }
    return new_tiles;
}

void generateCorridors(std::vector<std::pair<raylib::Vector2, raylib::Vector2>> mst, int* tiles, int width, int height) {

    int* corridor_tiles = downscale(tiles, width, height, HALLWAY_WIDTH);

    for (const auto& edge : mst) {
        raylib::Vector2 start = edge.first;
        raylib::Vector2 end = edge.second;

        start = start / HALLWAY_WIDTH;
        end = end / HALLWAY_WIDTH;

        // Floor the start and end points
        start.x = floor(start.x);
        start.y = floor(start.y);
        end.x = floor(end.x);
        end.y = floor(end.y);


        // We then pathfind from the start to the end
        std::vector<raylib::Vector2> path = findPath(start, end, corridor_tiles, width / HALLWAY_WIDTH, height / HALLWAY_WIDTH, [](raylib::Vector2 a, raylib::Vector2 b, int tile) {
            return Vector2Distance(a, b) - 0.5 * (tile == 0); // We subtract 0.5 if the tile is a floor tile so that the pathfinding prefers reuse hallways.
        });

        // We then draw the path
        for (const auto& point : path) {
            corridor_tiles[(int)point.x + (int)point.y * width / HALLWAY_WIDTH] = 0;
        }


    }

    int* new_tiles = upscale(corridor_tiles, width / HALLWAY_WIDTH, height / HALLWAY_WIDTH, HALLWAY_WIDTH);

    for (int i = 0; i < width * height; i++) {
        tiles[i] = new_tiles[i];
    }

}

void generateRooms(std::vector<raylib::Vector2> room_centers, int* tiles, int width, int height) {
    for (const auto& center : room_centers) {
        for (int x = -5; x < 5; x++) {
            for (int y = -5; y < 5; y++) {
                if (center.x + x >= 0 && center.x + x < width && center.y + y >= 0 && center.y + y < height) {
                    tiles[(int)(center.x + x) + (int)(center.y + y) * width] = 0;
                }
            }
        }
    }
}

void generateDungeon(Game* game, int width, int height) {
    
    TileSet tileSet = TileSet();
    tileSet.loadFromJson("assets/tileset.json"); // TODO: Load tileset randomly and turn this into a bin file using the packer.

    // Create a new dungeon
    int* tiles = new int[width * height];
    for (int i = 0; i < width * height; i++) {
        tiles[i] = -1;
    }

    // First we create a list of points
    std::vector<raylib::Vector2> room_centers;
    for (int i = 0; i < 64; i++) {
        room_centers.push_back(raylib::Vector2(GetRandomValue(0, width), GetRandomValue(0, height)));
    }

    // TODO: Load Rooms from files and do collision resolution.

    // Add a center room
    room_centers.push_back(raylib::Vector2(width / 2, height / 2));

    // Generate Delaunay Triangulation
    std::vector<std::pair<raylib::Vector2, raylib::Vector2>> triangles = generateDelaunayTriangulation(room_centers);

    // Generate Minimum Spanning Tree
    std::vector<std::pair<raylib::Vector2, raylib::Vector2>> mst = generateMinimumSpanningTree(triangles);

    // Generate Corridors
    generateCorridors(mst, tiles, width, height);

    // Generate Rooms
    generateRooms(room_centers, tiles, width, height);

    // Create the dungeon
    Dungeon* dungeon = new Dungeon(width, height, tiles, tileSet);

    entt::entity entity = game->getRegistry().create();
    game->getRegistry().emplace<Dungeon>(entity, *dungeon);

    // Add the rooms to the registry TODO: Add rooms to the dungeon

    // Add lights to every room
    for (const auto& center : room_centers) {
        // entt::entity light_entity = game->getRegistry().create();
        // game->getRegistry().emplace<Light>(light_entity, 32);
        // game->getRegistry().emplace<Position>(light_entity, center * TILE_SIZE);

        // Create a 32 dungeon spider in the room
        createDungeonSpider(game->getRegistry(), center * TILE_SIZE + raylib::Vector2{ TILE_SIZE / 2, TILE_SIZE / 2 });

        

    }

    // Place 32 candle randomly in the dungeon
    for (int i = 0; i < 32; i++) {
        while (true) {
            int x = GetRandomValue(0, width);
            int y = GetRandomValue(0, height);

            if (tiles[x + y * width] == 0) {
                createCandle(game, raylib::Vector2{ x * TILE_SIZE + TILE_SIZE / 2, y * TILE_SIZE + TILE_SIZE / 2 });
                break;
            }
        }
    }

    // Place a blood altar in a random room
    createBloodAltar(game, room_centers[room_centers.size() - 1] * TILE_SIZE + raylib::Vector2{ TILE_SIZE / 2, TILE_SIZE / 2 });

}