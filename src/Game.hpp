
#include <entt/entt.hpp>
#include <raylib-cpp.hpp>

class Game {

    public:
        Game();
        ~Game();

        void run();
        void render();
        void update(double dt);

        // TODO: Implement collision.
        void physicsSystem(double dt);
        void collisionSystem();
        void cameraFollowerSystem();

        entt::registry& getRegistry() {
            return registry;
        }

    private:

        entt::registry registry;
        raylib::Camera2D camera;

};