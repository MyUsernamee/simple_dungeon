
#include <entt/entt.hpp>
#include <raylib-cpp.hpp>
#include "data/Dungeon.hpp"
#include "unordered_map"
#include "spells/Spell.hpp"
#include "spells/CastDirection.hpp"

#pragma once

// Generic game class that contains the registry and systems
class Game {

    public:
        Game();
        ~Game();

        void run();
        void render();
        void update(double dt);

        entt::registry& getRegistry() {
            return registry;
        }
        
        void registerSystem(std::function<void(Game* game, double dt)> system) {
            systems.push_back(system);
        }
        void registerRenderSystem(std::function<void(Game* game, double dt)> system) {
            renderSystems.push_back(system);
        }
        // Used to set the systems in the game
        void setSystems(std::vector<std::function<void(Game* game, double dt)>> systems) {
            this->systems = systems;
        }
        void setRenderSystems(std::vector<std::function<void(Game* game, double dt)>> systems) {
            this->renderSystems = systems;
        }

        std::vector<std::function<void(Game* game, double dt)>>& getSystems() {
            return systems;
        }

        raylib::Camera2D& getCamera() {
            return camera;
        }

        std::vector<Spell>& getSpells() {
            return spells;
        }

        // Literally the same things as getting a dungeon from the registry, just a helper
        Dungeon& getDungeon() {
            
            auto view = registry.view<Dungeon>();

            // Get the first entity
            auto entity = *view.begin();

            return view.get<Dungeon>(entity);

        }

    protected: // Protected so that children that are used for testing can access them

        std::vector<std::function<void(Game* game, double dt)>> systems;
        std::vector<std::function<void(Game* game, double dt)>> renderSystems;

        entt::registry registry;
        raylib::Camera2D camera;

        std::vector<Spell> spells;

};