
#include <entt/entt.hpp>
#include <raylib-cpp.hpp>
#include "data/Dungeon.hpp"
#include "unordered_map"
#include "spells/Spell.hpp"
#include "spells/CastDirection.hpp"

#pragma once

class Game {

    public:
        Game();
        ~Game();

        void run();
        void render();
        void update(double dt);

        
        void physicsSystem(double dt);
        void collisionSystem();
        void cameraFollowerSystem();

        entt::registry& getRegistry() {
            return registry;
        }
        
        void setDungeon(Dungeon dungeon) {
            currentDungeon = dungeon;
        }

    private:

        entt::registry registry;
        raylib::Camera2D camera;
        Dungeon currentDungeon;
        std::vector<Spell>  spells;

};