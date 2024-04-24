#pragma once

#include <raylib-cpp.hpp>
#include <entt/entt.hpp>
#include "renderers/Renderer.hpp"
#include "spells/CastDirection.hpp"

#include <cereal/cereal.hpp>

#include <optional>
#include <functional>

/*

    This file contains all of the components that can be added to an entity.

*/

class Game; // Forward declaration

struct Renderable {

    Renderer* renderer;
    int z;
    int opacity = 255;

};

struct Player {

    raylib::Color color;
    int gamepad; // -1 if no gamepad
    entt::entity cursorEntity;

};

struct Position {

    raylib::Vector2 position;

};

struct Velocity {

    raylib::Vector2 velocity;

};

/**
 * @brief Basic class for defining a size of a object.
*/
struct Size {

    raylib::Vector2 size;

};

/**
 * @brief Adds collision to a object.
*/
struct Collision {

    int bitMask; // Bitmask for collision
    std::vector<entt::entity> collisions;

};

struct CameraFollower {

    int strength;
    raylib::Vector2 offset;

};

struct Health {

    Health(int health, int maxHealth) : health(health), maxHealth(maxHealth) {}

    int health;
    int maxHealth;

    void takeDamage(int damage)
    {
        health -= damage;
        if (health < 0)
        {
            health = 0;
        }
    }

};

struct Mana {

    Mana(int mana, int maxMana) : mana(mana), maxMana(maxMana) {}

    int mana;
    int maxMana;

};

// TODO: Merge SpellCaster and Mana
/**
 * @brief Adds the ability to cast spells to a object.
*/
struct SpellCaster {

    std::vector<CastDirection> currentCastDirections; // The current cast directions for the spell

    /**
     * @brief Adds a cast direction to the current cast directions and spawns particles.
     * @param registry The registry to spawn the particles in.
     * @param position The position to spawn the particles at.
     * @param direction The direction to add to the current cast directions.
    */
    void addCastDirection(entt::registry &registry, raylib::Vector2 position, CastDirection direction); // Add a cast direction to the current cast directions and spawn particles
    void cast(Game* game, entt::entity entity, raylib::Vector2 direction); // Cast the spell

};

struct AI {

    double speed;
    raylib::Vector2 movement;

};

struct Team {

    int teamBitMask; // Bitmask for team If these are & together and they are not 0 then they are on the same team. and should not attack each other.

};

struct MeleeEnemy {

    int attackSpeed;
    int attackTimer;
    double range;
    int damage;

};

struct Projectile {

    int damage;
    double lifeTime;
    double speed;
    raylib::Vector2 direction;

    std::optional<std::function<void(Game* game, entt::entity entity, entt::entity other)>> onHit;

};

struct Particle {

    raylib::Vector2 gravity;
    raylib::Vector2 random_scale;
    double lifeTime;

    template <class Archive>
    void serialize(Archive &archive)
    {
        archive(CEREAL_NVP(gravity), CEREAL_NVP(random_scale), CEREAL_NVP(lifeTime), CEREAL_NVP(texture), CEREAL_NVP(color));
    }

};

struct ParticleSystem {

    Particle particle; // The particle to spawn
    double spawnRate; // The rate to spawn the particles
    double spawnTimer; // The timer to spawn the particles
    int maxParticles; // The maximum amount of particles to spawn


};

/**
 * Changes the opacity of the renderable based on the health of the entity.
*/
struct DungeonOcclusion {

    

};