#include <raylib-cpp.hpp>
#include "AStar.hpp"
#include <vector>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include <functional>

// Define directions for 4 possible neighbors (assuming 8-direction movement)
const std::vector<raylib::Vector2> directions = {
    raylib::Vector2{0, -1}, // Up
    raylib::Vector2{1, 0},  // Right
    raylib::Vector2{0, 1},  // Down
    raylib::Vector2{-1, 0}  // Left
};

// Assuming a simple Manhattan distance heuristic for grid-based pathfinding
double def_heuristic(raylib::Vector2 current, raylib::Vector2 goal, int tile) {
    return std::abs(current.x - goal.x) + std::abs(current.y - goal.y) - (tile != 0 ? 0.5 : 0);
}

std::vector<raylib::Vector2> findPath(raylib::Vector2 start, raylib::Vector2 end, int* map, int mapWidth, int mapHeight, std::function<double(raylib::Vector2, raylib::Vector2, int)> heuristic) {
    
    // We floor the start and end points to get the cell position
    start.x = floor(start.x);
    start.y = floor(start.y);
    end.x = floor(end.x);
    end.y = floor(end.y);
    
    
    std::vector<raylib::Vector2> open_set;
    std::unordered_map<raylib::Vector2, raylib::Vector2> cameFrom;

    std::unordered_map<raylib::Vector2, double> gScore;
    open_set.push_back(start);
    gScore[start] = heuristic(start, end, map[(int)start.y * mapWidth + (int)start.x]);

    // Check if the start and end points are in the map bounds
    if (start.x < 0 || start.x >= mapWidth || start.y < 0 || start.y >= mapHeight) {
        return std::vector<raylib::Vector2>(); // No path found
    }
    if (end.x < 0 || end.x >= mapWidth || end.y < 0 || end.y >= mapHeight) {
        return std::vector<raylib::Vector2>(); // No path found
    }

    while (!open_set.empty()) {
        raylib::Vector2 current;
        double lowest = std::numeric_limits<double>::max();

        // Find the cell in open_set with the lowest gScore
        for (auto& node : open_set) {
            if (gScore[node] < lowest) {
                lowest = gScore[node];
                current = node;
            }
        }

        if (current == end) {
            // Reconstruct the path from end to start
            std::vector<raylib::Vector2> path;
            while (current != start) {
                path.push_back(current);
                current = cameFrom[current];
            }
            path.push_back(start); // Add start point to path
            std::reverse(path.begin(), path.end()); // Reverse path to start -> end order
            return path;
        }

        open_set.erase(std::remove(open_set.begin(), open_set.end(), current), open_set.end());

        // Explore neighbors (8-direction movement)
        for (const auto& direction : directions) {
            raylib::Vector2 neighbor = current + direction;
            if (neighbor.x < 0 || neighbor.x >= mapWidth || neighbor.y < 0 || neighbor.y >= mapHeight) {
                continue; // Skip out-of-bounds neighbors
            }

            if (gScore.find(current) == gScore.end()) {
                gScore[current] = std::numeric_limits<double>::max(); // Initialize to infinity
            }

            double tentative_gScore = heuristic(current, neighbor, map[(int)neighbor.y * mapWidth + (int)neighbor.x]) + gScore[current];

            if (gScore.find(neighbor) == gScore.end()) {
                gScore[neighbor] = std::numeric_limits<double>::max(); // Initialize to infinity
            }

            // Breakpoint if gScore[neighbor] is 0      
            // TraceLog(LOG_INFO, "gScore[%d]: %f", (int)neighbor.y * mapWidth + (int)neighbor.x, gScore[neighbor]);

            if (tentative_gScore < gScore[neighbor]) {
                cameFrom[neighbor] = current;
                gScore[neighbor] = tentative_gScore;
                
                if (std::find(open_set.begin(), open_set.end(), neighbor) == open_set.end()) {
                    open_set.push_back(neighbor);
                }

            }
        }
    }

    return std::vector<raylib::Vector2>(); // No path found
}