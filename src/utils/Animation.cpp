#include "Animation.hpp"
#include "TextureCache.hpp"

Animation::Animation()
{

    frames = std::vector<Texture2D>();

}

Animation::Animation(char* path_pattern)
{

    frames = std::vector<Texture2D>();

    load(path_pattern);

}

void Animation::load(char* path_pattern)
{

    int index = 0;
    bool loaded = true;

    // If the animation starts at 1 instead of 0
    if (!FileExists(TextFormat(path_pattern, 0)) && FileExists(TextFormat(path_pattern, 1))) {
        index = 1;
    }

    while (loaded) {

        char path[256];
        sprintf(path, path_pattern, index);

        Texture2D frame = LoadTextureCached(path);

        if (frame.id == 0) {

            loaded = false;

        } else {

            frames.push_back(frame);

        }

        index++;

    }

}

Texture2D Animation::getFrame(int index)
{

    return frames[index];

}

Animation::~Animation()
{

    // Do nothing.

}