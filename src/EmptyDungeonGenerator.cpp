#include "EmptyDungeonGenerator.hpp"
#include "overlapping_wfc.hpp"
#include "AStar.hpp"
#include <unordered_set>
#include <delaunator.hpp>
#include <set>

const int HALLWAY_WIDTH = 4;

EmptyDungeonGenerator::EmptyDungeonGenerator() {

    tileSet = TileSet("assets/0x72_DungeonTilesetII_v1.7/atlas_floor-16x16.png", 16);

    int floorCount = tileSet.getTileCount();

    tileSet.load("assets/0x72_DungeonTilesetII_v1.7/atlas_walls_high-16x32.png", 16);

    // Make every tile after the floor tiles solid
    for (int i = floorCount; i < tileSet.getTileCount(); i++) {
        tileSet.getTile(i).solid = true;
    }

}


std::vector<std::pair<raylib::Vector2, raylib::Vector2>> findMST(std::vector<std::pair<raylib::Vector2, raylib::Vector2>> edges) {
    std::vector<std::pair<raylib::Vector2, raylib::Vector2>> mst;

    if (edges.empty())
        return mst;  // No edges to process

    // Collect all unique vertices from the edges
    std::unordered_set<raylib::Vector2> vertices;
    for (const auto& edge : edges) {
        vertices.insert(edge.first);
        vertices.insert(edge.second);
    }

    if (vertices.size() <= 1)
        return mst;  // If only one vertex, no MST can be formed

    // Initialize the MST construction with the first vertex
    std::unordered_set<raylib::Vector2> visited;
    visited.insert(*vertices.begin());  // Start with the first vertex

    // Continue until all vertices are visited
    while (visited.size() < vertices.size()) {
        double lowest = std::numeric_limits<double>::max();
        std::pair<raylib::Vector2, raylib::Vector2> lowestEdge;

        // Find the next edge connecting a visited vertex to an unvisited vertex
        for (const auto& edge : edges) {
            if (visited.count(edge.first) + visited.count(edge.second) == 1) {  // One vertex visited, one unvisited
                double distance = edge.first.Distance(edge.second);
                if (distance < lowest) {
                    lowest = distance;
                    lowestEdge = edge;
                }
            }
        }

        // Add the lowest weight edge to the MST
        if (lowestEdge.first != lowestEdge.second) {  // Avoid self-loops
            mst.push_back(lowestEdge);
            // Mark both endpoints of the edge as visited
            visited.insert(lowestEdge.first);
            visited.insert(lowestEdge.second);
        } else {
            // If no valid edge is found (e.g., due to disconnected components), break the loop
            break;
        }
    }

    return mst;
}

// Add hash for std::pair<raylib::Vector2, raylib::Vector2>
namespace std {
    template <>
    struct hash<std::pair<raylib::Vector2, raylib::Vector2>> {
        std::size_t operator()(const std::pair<raylib::Vector2, raylib::Vector2>& k) const {
            return std::hash<double>()(k.first.x) ^ std::hash<double>()(k.first.y) ^ std::hash<double>()(k.second.x) ^ std::hash<double>()(k.second.y);
        }
    };
}

void waitForKeypress() {
    EndDrawing();
    while (!IsKeyPressed(KEY_SPACE)) {
        BeginDrawing();
        DrawText("Press SPACE to continue", 10, 10, 20, WHITE);
        EndDrawing();
    }
    BeginDrawing();
}

Dungeon EmptyDungeonGenerator::generateDungeon(int width, int height) {
    
    // Walls are solid
    int* tiles = new int[width * height];
    // WE initialize everything with -1
    for (int i = 0; i < width * height; i++) {
        tiles[i] = 0;
    }

    // We create rooms
    std::vector<raylib::Vector2> rooms;
    for (int i = 0; i < 32; i++) { // TODO: Make this generic, remove magic numbers
        rooms.push_back(raylib::Vector2(GetRandomValue(0, width), GetRandomValue(0, height)));
    }

    // Add a starting room at the center
    rooms.push_back(raylib::Vector2(width / 2, height / 2));


    std::vector<double> points;
    for (const auto& p : rooms) {
        points.push_back(p.x);
        points.push_back(p.y);
    }

    delaunator::Delaunator d(points);

    std::vector<raylib::Vector2> delaunayPoints;

    for (int i = 0; i < d.triangles.size(); i += 3) {
        raylib::Vector2 a = raylib::Vector2(d.coords[2 * d.triangles[i]], d.coords[2 * d.triangles[i] + 1]);
        raylib::Vector2 b = raylib::Vector2(d.coords[2 * d.triangles[i + 1]], d.coords[2 * d.triangles[i + 1] + 1]);
        raylib::Vector2 c = raylib::Vector2(d.coords[2 * d.triangles[i + 2]], d.coords[2 * d.triangles[i + 2] + 1]);

        delaunayPoints.push_back(a);
        delaunayPoints.push_back(b);
        delaunayPoints.push_back(c);
    }

    // Get the graph edges
    std::vector<std::pair<raylib::Vector2, raylib::Vector2>> edges;

    for (int i = 0; i < delaunayPoints.size(); i++) {
        for (int j = 0; j < delaunayPoints.size(); j++) {
            if (i != j) {
                edges.push_back(std::make_pair(delaunayPoints[i], delaunayPoints[j]));
            }
        }
    }

    // Deduplicate the edges
    std::unordered_set<std::pair<raylib::Vector2, raylib::Vector2>> dedupedEdges;
    for (const auto& edge : edges) {
        dedupedEdges.insert(edge);
    }

    edges.clear();
    for (const auto& edge : dedupedEdges) {
        edges.push_back(edge);
    }

    // Find MST (Minimum Spanning Tree) using the delaunay triangulation
    std::vector<std::pair<raylib::Vector2, raylib::Vector2>> mst;
    mst = findMST(edges);

    // Choose a couple random edges and add them to the MST so we have some loops
    for (int i = 0; i < 5; i++) {
        mst.push_back(edges[GetRandomValue(0, edges.size() - 1)]);
    }

    // WaitTime(10);

    // Downscale the map for AStar so our hallways are larger
    int* downscale = new int[width / HALLWAY_WIDTH * height / HALLWAY_WIDTH];
    for (int i = 0; i < width / HALLWAY_WIDTH * height / HALLWAY_WIDTH; i++) {
        downscale[i] = 0;
    }


    // Pathfind between each pair of points in the MST
    for (const auto& edge : mst) {
        raylib::Vector2 start = edge.first;
        raylib::Vector2 end = edge.second;

        // Downscaled start
        raylib::Vector2 flooredStart = raylib::Vector2(floor(start.x / HALLWAY_WIDTH), floor(start.y / HALLWAY_WIDTH));
        raylib::Vector2 flooredEnd = raylib::Vector2(floor(end.x / HALLWAY_WIDTH), floor(end.y / HALLWAY_WIDTH));

        std::vector<raylib::Vector2> path = findPath(flooredStart, flooredEnd, downscale, width / HALLWAY_WIDTH, height / HALLWAY_WIDTH);

        TraceLog(LOG_INFO, "Path from (%f, %f) to (%f, %f)", start.x, start.y, end.x, end.y);
        TraceLog(LOG_INFO, "Path size: %i", path.size());

        for (const auto& p : path) {
            downscale[(int)p.y * width / HALLWAY_WIDTH + (int)p.x] = 1;
        }
    }

    // Upscale the map
    for (int y = 0; y < height; y += HALLWAY_WIDTH) {
        for (int x = 0; x < width; x += HALLWAY_WIDTH) {
            for (int i = 0; i < HALLWAY_WIDTH; i++) {
                for (int j = 0; j < HALLWAY_WIDTH; j++) {

                    if (y + i >= height || x + j >= width)
                        continue;

                    tiles[(y + i) * width + (x + j)] = downscale[(y / HALLWAY_WIDTH) * width / HALLWAY_WIDTH + x / HALLWAY_WIDTH];
                }
            }
        }
    }

    // We then create a room for each point
    for (const auto& p : rooms) {
        int roomWidth = GetRandomValue(8, 32);
        int roomHeight = GetRandomValue(8, 32);

        for (int y = p.y - roomHeight / 2; y < p.y + roomHeight / 2; y++) {
            for (int x = p.x - roomWidth / 2; x < p.x + roomWidth / 2; x++) {

                if (y < 0 || x < 0 || y >= height || x >= width)
                    continue;

                tiles[y * width + x] = 1;
            }
        }
    }

    // Subtract 1 from every tile
    for (int i = 0; i < width * height; i++) {
        tiles[i] = tiles[i] - 1;
    }

    return Dungeon(width, height, tiles, tileSet);

}