
#include <entt/entt.hpp>
#include <raylib-cpp.hpp>
#include "data/Dungeon.hpp"
#include "unordered_map"
#include "spells/Spell.hpp"

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

        // Literally the same things as getting a dungeon from the registry, just a helper
        Dungeon& getDungeon() {
            
            auto view = registry.view<Dungeon>();

            // Get the first entity
            auto entity = *view.begin();

            return view.get<Dungeon>(entity);

        }

        // Get the spell cache
        entt::resource_cache<Spell*>& getSpellCache() {
            return spellCache;
        }

        entt::resource<Spell*> getSpell(entt::id_type id) {
            return spellCache[id];
        }

        void registerSpell(const entt::id_type id, Spell* spell) {
            spellCache.load(id, spell);
        }


    protected: // Protected so that children that are used for testing can access them

        std::vector<std::function<void(Game* game, double dt)>> systems;
        // The order of rendering systems is guaranteed by the order of insertion
        // All systems are rendered after all entities.
        std::vector<std::function<void(Game* game, double dt)>> renderSystems;

        entt::registry registry;
        raylib::Camera2D camera;

        Shader lightShader;
        RenderTexture2D target;
        RenderTexture2D lightTarget;

        entt::resource_cache<Spell*> spellCache; // Stores all spells

};