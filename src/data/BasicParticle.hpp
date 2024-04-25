
#pragma once

#include <raylib-cpp.hpp>
#include <cereal/cereal.hpp>

struct BasicParticle {

    raylib::Vector2 random_scale;
    raylib::Vector2 gravity;
    double lifeTime;
    char texture_path[256];
    raylib::Color color;

    template <class Archive>
    void serialize(Archive & archive)
    {
        archive(
            CEREAL_NVP(random_scale),
            CEREAL_NVP(gravity),
            CEREAL_NVP(lifeTime),
            CEREAL_NVP(texture_path),
            CEREAL_NVP(color)
        );
    }

};