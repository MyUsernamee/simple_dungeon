#include <raylib-cpp.hpp>

#pragma once

class Animation {

    public:

        Animation();
        /**
         * @brief Construct a new Animation object
         * Loads a animation from a path pattern.
         * @example Animation("assets/sprites/player/player_%d.png");
        */
        Animation(char* path_pattern);
        ~Animation();

        /**
         * @brief Load a animation from a path pattern.
         * @example load("assets/sprites/player/player_%d.png");
        */
        void load(char* path_pattern);

        Texture2D getFrame(int index);
        int getFrameCount() { return frames.size(); }

    private:

        std::vector<Texture2D> frames;


};