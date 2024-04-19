
#include <raylib-cpp.hpp>

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

};

struct CameraFollower {

    int strength;
    raylib::Vector2 offset;

};

struct Health {

    int health;
    int maxHealth;

};