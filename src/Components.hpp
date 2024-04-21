#pragma once

#include <raylib-cpp.hpp>
#include <entt/entt.hpp>
#include "renderers/Renderer.hpp"

struct Renderable {

    Renderer* renderer;
    int z;

};

struct Player {

    raylib::Color color;
    int gamepad; // -1 if no gamepad

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
    entt::sigh<void(entt::registry &, entt::entity, entt::entity)> onCollisionSignal;


};

struct CameraFollower {

    int strength;
    raylib::Vector2 offset;

};

struct Health {

    Health(int health, int maxHealth) : health(health), maxHealth(maxHealth) {}

    int health;
    int maxHealth;
    entt::sigh<void()> onDamage;
    entt::sigh<void()> onDeath;
    void takeDamage(int damage) {
        health -= damage;
        if (health <= 0) {
            onDeath.publish();
        }
        else {
            onDamage.publish();
        }
    
    }

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
    int lifeTime;
    double speed;
    raylib::Vector2 direction;

};