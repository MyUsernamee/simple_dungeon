
#include <entt/entt.hpp>

class Game {

    public:
        Game();
        ~Game();

        void run();
        void render();
        void update(double dt);

        // TODO: Implement collision.

    private:

        entt::registry registry;

};