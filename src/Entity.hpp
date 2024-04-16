
#include <raylib-cpp.hpp>

class Game; // Forward declaration

class Entity {

    public:
        Entity();
        ~Entity();

        virtual void render() = 0;
        virtual void update(double dt, Game* game) = 0;

        void setVelocity(raylib::Vector2 velocity);
        raylib::Vector2 getVelocity();

        void setPosition(raylib::Vector2 position);
        raylib::Vector2 getPosition();

        void setRectangle(raylib::Rectangle rectangle);
        raylib::Rectangle getRectangle();

        void setSize(raylib::Vector2 size);
        raylib::Vector2 getSize();

        virtual void onCollision(Entity* entity) = 0; // TODO: Implement all of these

    private:

        raylib::Vector2 velocity;
        raylib::Rectangle rectangle;

};