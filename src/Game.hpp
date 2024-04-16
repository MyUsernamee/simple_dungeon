
#include <vector>

class Game {

    public:
        Game();
        ~Game();

        void run();
        void render();
        void update(double dt);

        // TODO: Implement collision.

    private:

        std::vector<Player> players;
        std::vector<Enemy> enemies;

};