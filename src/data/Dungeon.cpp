#include "data/Dungeon.hpp"
#include <algorithm>
#include "utils/AStar.hpp"

Dungeon::Dungeon(int width, int height, int *tiles, TileSet tileSet)
{

    this->width = width;
    this->height = height;
    this->tiles = tiles;
    this->tileSet = tileSet;

    this->opacity = new double[width * height];

    for (int i = 0; i < width * height; i++) {
        opacity[i] = 0;
    }

}

Dungeon::Dungeon()
{

    width = 0;
    height = 0;
    tiles = nullptr;
    tileSet = TileSet();

}

Dungeon::~Dungeon()
{

    //delete[] tiles;

}

void Dungeon::render(raylib::Camera2D camera, std::vector<std::pair<raylib::Vector2, double>> visiblity_points)
{

    int start_x = ((int)camera.target.x - (int)camera.offset.x) / TILE_SIZE;
    int start_y = ((int)camera.target.y - (int)camera.offset.y) / TILE_SIZE;

    int end_x = start_x + GetRenderWidth() / TILE_SIZE + 1;
    int end_y = start_y + GetRenderHeight() / TILE_SIZE + 2;
    
    for (int y = start_y; y < end_y; y++) {

        for (int x = start_x; x < end_x; x++) {
            if (x < 0 || x >= width || y < 0 || y >= height) continue; // TODO: Make this use a clamp function instead of if statements
            if (tiles[y * width + x] == -1) continue;

            double visibility = 0.0;
            for (int i = 0; i < visiblity_points.size(); i++) {
                float distance = visiblity_points[i].first.Distance(raylib::Vector2(x * TILE_SIZE, y * TILE_SIZE)) / TILE_SIZE;

                if (distance > visiblity_points[i].second) continue;

                if (!rayCast(raylib::Vector2(x * TILE_SIZE, y * TILE_SIZE), visiblity_points[i].first, nullptr)) {

                    visibility = std::max(visibility, visiblity_points[i].second / pow(distance, 2.0));
                    

                }   
            }


            visibility = std::clamp(visibility, 0.2, 1.0);
            opacity[y * width + x] += (visibility - opacity[y * width + x]) * 0.1;

            Tile tile = tileSet.getTile(tiles[y * width + x]);

            Texture2D texture = tile.textures[tile.currentTexture];

            DrawTextureEx(texture, {(float)x * TILE_SIZE, (float)y * TILE_SIZE}, 0, TILE_SIZE / texture.width, {255, 255, 255, static_cast<unsigned char>(255 * opacity[y * width + x])});
        }

    }

}

bool Dungeon::rayCast(raylib::Vector2 start, raylib::Vector2 end, float *outDistance) // TODO: Optimize, and also split into two functions one for raycast and one for line of sight
{
    
    raylib::Vector2 dir = end - start;
    float dist = dir.Length();
    dir = dir.Normalize();
    raylib::Vector2 current = start;

    for (float i = 0; i < dist; i += 1) {

        if (tiles[(int)floor(current.y / TILE_SIZE) * width + (int)floor(current.x / TILE_SIZE)] == -1) {
            if (outDistance != nullptr) *outDistance = i;
            return true;
        }

        current += dir;

    }

    return false;

}

double h(raylib::Vector2 a, raylib::Vector2 b)
{
    return a.Distance(b) + GetRandomValue(0, 100) / 25.0;
}// Define directions for 4 possible neighbors (assuming 8-direction movement)
const std::vector<raylib::Vector2> directions = {
    raylib::Vector2{0, -1}, // Up
    raylib::Vector2{1, 0},  // Right
    raylib::Vector2{0, 1},  // Down
    raylib::Vector2{-1, 0}  // Left
};

std::vector<raylib::Vector2> Dungeon::pathFind(raylib::Vector2 start, raylib::Vector2 end)
{

    start = start / TILE_SIZE;
    end = end / TILE_SIZE;

    if (start.x < 0 || start.x >= width || start.y < 0 || start.y >= height) return {};
    if (end.x < 0 || end.x >= width || end.y < 0 || end.y >= height) return {};
    if (tileSet.getTile(tiles[(int)start.y * width + (int)start.x]).getBoolProperty("solid")) return {};
    if (tileSet.getTile(tiles[(int)end.y * width + (int)end.x]).getBoolProperty("solid")) return {};

    
    // We floor the start and end points to get the cell position
    start.x = floor(start.x);
    start.y = floor(start.y);
    end.x = floor(end.x);
    end.y = floor(end.y);
    
    
    std::vector<raylib::Vector2> open_set;
    std::unordered_map<raylib::Vector2, raylib::Vector2> cameFrom;

    std::unordered_map<raylib::Vector2, double> gScore;
    open_set.push_back(start);
    gScore[start] = h(start, end);

    // Check if the start and end points are in the map bounds
    if (start.x < 0 || start.x >= width || start.y < 0 || start.y >= height) {
        return std::vector<raylib::Vector2>(); // No path found
    }
    if (end.x < 0 || end.x >= width || end.y < 0 || end.y >= height) {
        return std::vector<raylib::Vector2>(); // No path found
    }
    std::vector<raylib::Vector2> path;

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
            while (current != start) {
                path.push_back(current + raylib::Vector2(0.5, 0.5)); // Add 0.5 to get the center of the cell
                current = cameFrom[current]; // Add 0.5 to get the center of the cell
            }
            path.push_back(start + raylib::Vector2(0.5, 0.5)); // Add 0.5 to get the center of the cell
            std::reverse(path.begin(), path.end()); // Reverse path to start -> end order
            
            break;
        }

        open_set.erase(std::remove(open_set.begin(), open_set.end(), current), open_set.end());

        // Explore neighbors (8-direction movement)
        for (const auto& direction : directions) {
            raylib::Vector2 neighbor = current + direction;
            if (neighbor.x < 0 || neighbor.x >= width || neighbor.y < 0 || neighbor.y >= height) {
                continue; // Skip out-of-bounds neighbors
            }
            if (getTile(neighbor.x, neighbor.y).getBoolProperty("solid") || getTile(neighbor.x, neighbor.y).textures.size() == 0) {
                continue; // Skip solid neighbors
            }

            if (gScore.find(current) == gScore.end()) {
                gScore[current] = std::numeric_limits<double>::max(); // Initialize to infinity
            }

            double tentative_gScore = h(current, neighbor) + gScore[current];

            if (gScore.find(neighbor) == gScore.end()) {
                gScore[neighbor] = std::numeric_limits<double>::max(); // Initialize to infinity
            }

            // Breakpoint if gScore[neighbor] is 0      
            // TraceLog(LOG_INFO, "gScore[%d]: %f", (int)neighbor.y * width + (int)neighbor.x, gScore[neighbor]);

            if (tentative_gScore < gScore[neighbor]) {
                cameFrom[neighbor] = current;
                gScore[neighbor] = tentative_gScore;
                
                if (std::find(open_set.begin(), open_set.end(), neighbor) == open_set.end()) {
                    open_set.push_back(neighbor);
                }

            }
        }
    }

    // Multiply by TILE_SIZE
    for (int i = 0; i < path.size(); i++) {
        path[i] *= TILE_SIZE;
    } // TODO: Make this not scale by TILE_SIZE

    return path;
}
