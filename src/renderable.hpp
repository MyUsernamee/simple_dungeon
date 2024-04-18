
#pragma once

#include <entt/entt.hpp>

class renderable {

    public:

        virtual void render(const entt::registry& registry, const entt::entity& entity) = 0; // Pure virtual function

        int z;

    private:

        // Do nothing

};