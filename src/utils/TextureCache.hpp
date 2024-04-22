#include "../../dependencies/raylib-cpp/include/Texture.hpp"
#include <unordered_map>
#include <string>

#pragma once

/**
 * @brief Works the exact same way as LoadTexture, but caches the texture to avoid loading the same texture multiple times.
*/
Texture LoadTextureCached(const std::string& path);