
#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>

#include "utils/TileSet.hpp"

// Takes a json file and turns it into a .tileset file.
int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path to tileset file>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    nlohmann::json j;
    file >> j;

    

    return 0;
}