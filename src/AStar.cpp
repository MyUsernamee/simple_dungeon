#include "AStar.hpp"
#include <vector>
#include <map>
#include <set>

const raylib::Vector2* directions = new raylib::Vector2[8] {
    raylib::Vector2(1, 0),
    raylib::Vector2(1, 1),
    raylib::Vector2(0, 1),
    raylib::Vector2(-1, 1),
    raylib::Vector2(-1, 0),
    raylib::Vector2(-1, -1),
    raylib::Vector2(0, -1),
    raylib::Vector2(1, -1)
};

double heuristic(raylib::Vector2 a, raylib::Vector2 b)
{
    return a.Distance(b);
}

std::vector<raylib::Vector2> findPath(raylib::Vector2 start, raylib::Vector2 end, int* map, int mapWidth, int mapHeight)
{
    std::set<raylib::Vector2> open_set;
    std::map<raylib::Vector2, raylib::Vector2> cameFrom;

    open_set.insert(start);

    std::map<raylib::Vector2, int> gScore;
    gScore[start] = heuristic(start, end);

    while (!open_set.empty())
    {
        raylib::Vector2 current;
        double lowest = std::numeric_limits<double>::max();

        for (auto &node : open_set)
        {
            if (gScore[node] < lowest)
            {
                lowest = gScore[node];
                current = node;
            }
        }

        if (current == end)
        {
            std::vector<raylib::Vector2> path;
            while (current != start)
            {
                path.push_back(current);
                current = cameFrom[current];
            }
            return path;
        }

        open_set.erase(current);
        
        for (int i = 0; i < 8; i++)
        {
            raylib::Vector2 neighbor = current + directions[i];
            if (neighbor.x < 0 || neighbor.x >= mapWidth || neighbor.y < 0 || neighbor.y >= mapHeight)
            {
                continue;
            }

            if (map[(int)neighbor.y * mapWidth + (int)neighbor.x] == 1)
            {
                continue;
            }

            double tentative_gScore = gScore[current] + heuristic(current, neighbor);

            if (tentative_gScore < gScore[neighbor])
            {
                cameFrom[neighbor] = current;
                gScore[neighbor] = tentative_gScore;
                open_set.insert(neighbor);
            }
        }

    }



    return std::vector<raylib::Vector2>(); // No path found
}