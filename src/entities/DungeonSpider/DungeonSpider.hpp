
#pragma once

#include "ai/AiBrain.hpp"

class DungeonSpider : public AiBrain {

    enum struct State {
        IDLE,
        WALKING,
        ATTACKING
    };

    public:

        DungeonSpider() = default;

        State state = State::IDLE;
        void update(Game* game, entt::entity entity) override;

};