#pragma once

#include <raylib-cpp.hpp>
#include <entt/entt.hpp>
#include "renderers/Renderer.hpp"
#include "Game.hpp"

/*

    This file contains all of the components that can be added to an entity.

*/

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