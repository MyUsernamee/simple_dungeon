
#pragma once

#include <entt/entt.hpp>

class Renderer {

    public:

        virtual void render(const entt::registry& registry, const entt::entity& entity) = 0; // Pure virtual function

    private:

        // Do nothing

};