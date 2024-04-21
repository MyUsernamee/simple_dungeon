#include "Dungeon.hpp"
#include <algorithm>
#include "AStar.hpp"

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

void Dungeon::render(raylib::Camera2D camera, std::vector<raylib::Vector2> visiblity_points)
{

    int start_x = ((int)camera.target.x - (int)camera.offset.x) / TILE_SIZE;
    int start_y = ((int)camera.target.y - (int)camera.offset.y) / TILE_SIZE;

    int end_x = start_x + GetRenderWidth() / TILE_SIZE + 1;
    int end_y = start_y + GetRenderHeight() / TILE_SIZE + 2;
    
    for (int y = start_y; y < end_y; y++) {

        for (int x = start_x; x < end_x; x++) {
            if (x < 0 || x >= width || y < 0 || y >= height) continue; // TODO: Make this use a clamp function instead of if statements
            if (tiles[y * width + x] == -1) continue;

            bool visible = false;
            for (int i = 0; i < visiblity_points.size(); i++) {
                if (!rayCast(raylib::Vector2(x * TILE_SIZE, y * TILE_SIZE), visiblity_points[i], nullptr)) {

                    visible = true;
                    break;

                }   
            }

            if (visible) {

                opacity[y * width + x] = std::min(1.0, opacity[y * width + x] + GetFrameTime() * 2.0);

            }
            else {

                opacity[y * width + x] = std::max(0.0, opacity[y * width + x] - GetFrameTime());

            }

            

            Tile tile = tileSet.getTile(tiles[y * width + x]);

            DrawTextureEx(tile.texture, {(float)x * TILE_SIZE, (float)y * TILE_SIZE}, 0, TILE_SIZE / tile.texture.width, raylib::Color{255, 255, 255, (unsigned char)(opacity[y * width + x] * 255)});

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

double heuristic(raylib::Vector2 a, raylib::Vector2 b, int tile)
{
    // Max if the tile is solid
    return a.Distance(b) + (tile == 1 ? 10000000 : 0);
}

std::vector<raylib::Vector2> Dungeon::pathFind(raylib::Vector2 start, raylib::Vector2 end)
{

    start = start / TILE_SIZE;
    end = end / TILE_SIZE;

    if (start.x < 0 || start.x >= width || start.y < 0 || start.y >= height) return {};
    if (end.x < 0 || end.x >= width || end.y < 0 || end.y >= height) return {};
    if (tileSet.getTile(tiles[(int)start.y * width + (int)start.x]).solid) return {};
    if (tileSet.getTile(tiles[(int)end.y * width + (int)end.x]).solid) return {};
    
    int* map = new int[width * height];
    for (int i = 0; i < width * height; i++) {
        map[i] = tileSet.getTile(tiles[i]).solid ? 1 : 0;
    }

    std::vector<raylib::Vector2> path = findPath(start, end, map, width, height, heuristic);

    // Multiply by TILE_SIZE
    for (int i = 0; i < path.size(); i++) {
        path[i] *= TILE_SIZE;
    } // TODO: Make this not scale by TILE_SIZE

    delete[] map;

    return path;
}
