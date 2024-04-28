
#include <raylib-cpp.hpp>
#include "generators/DungeonGenerator.hpp"

#include "Game.hpp"
#include <generators/SimpleDungeonGenerator.hpp>

class TestGame: public Game {

    public:

        TestGame() {}
        ~TestGame() {}

        void render() {

            getCamera().BeginMode();

            getDungeon().render(getCamera(), {getCamera().target});

            getCamera().EndMode();

            if (IsKeyDown(KEY_UP)) camera.target.y -= 10;
            if (IsKeyDown(KEY_DOWN)) camera.target.y += 10;
            if (IsKeyDown(KEY_LEFT)) camera.target.x -= 10;
            if (IsKeyDown(KEY_RIGHT)) camera.target.x += 10;

        }

        void setCamera(raylib::Camera2D camera) {
            this->camera = camera;
        }


};


int main () {

    raylib::Window w(800, 600, "Dungeon Generator Test");
    
    w.SetTargetFPS(60);

    TestGame game = TestGame();
    game.getCamera().target = {256 * TILE_SIZE, 256 * TILE_SIZE};

    generateDungeon(&game, 512, 512);

    while (!w.ShouldClose()) {

        w.BeginDrawing();
        w.ClearBackground(BLACK);

        game.run();

        if (IsKeyDown(KEY_W)) game.getCamera().target.y -= 10;
        if (IsKeyDown(KEY_S)) game.getCamera().target.y += 10;
        if (IsKeyDown(KEY_A)) game.getCamera().target.x -= 10;
        if (IsKeyDown(KEY_D)) game.getCamera().target.x += 10;

        w.EndDrawing();

    }


}
