#include "CastTexture.hpp"
#include <spells/CastDirection.hpp>

Texture castDirectionToTexture(CastDirection direction) {
    switch (direction) {
        case CastDirection::UP:
            return LoadTextureCached("assets/particles/up.png");
        case CastDirection::DOWN:
            return LoadTextureCached("assets/particles/down.png");
        case CastDirection::LEFT:
            return LoadTextureCached("assets/particles/left.png");
        case CastDirection::RIGHT:
            return LoadTextureCached("assets/particles/right.png");
    }
}
