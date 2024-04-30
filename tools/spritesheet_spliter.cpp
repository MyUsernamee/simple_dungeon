#include <raylib-cpp.hpp>
#include <iostream>
#include <vector>

/*

    Sprite sheet spliter. Takes a sprite sheet and lets you export the indivusal frames with a named convetion.

    For example:
    spider_walk_f0.png
    spider_walk_f1.png
    spider_walk_f2.png
    etc..

*/
int main (int argc, char* argv[]) {

    if (argc < 4) {
        std::cout << "Usage: " << argv[0] << " <sprite_sheet> <output_dir> <num_frames_vertical> <nume_frames_horizontal>" << std::endl;
        return 1;
    }

    std::string sprite_sheet_path = argv[1];
    std::string output_dir = argv[2];
    int num_frames_vertical = std::stoi(argv[3]);
    int num_frames_horizontal = std::stoi(argv[4]);

    std::vector<std::pair<int, int>> frames;

    raylib::Image sprite_sheet = Load(sprite_sheet_path);



}