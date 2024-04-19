#include "Animation.hpp"

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

    while (loaded) {

        char path[256];
        sprintf(path, path_pattern, index);

        Texture2D frame = LoadTexture(path);

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