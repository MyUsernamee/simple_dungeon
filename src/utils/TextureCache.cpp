
#include "TextureCache.hpp"

Texture LoadTextureCached(const std::string &path) {
    static std::unordered_map<std::string, Texture> cache;

    if (cache.find(path) == cache.end()) {
        cache[path] = LoadTexture(path.c_str());
    }

    return cache[path];
}