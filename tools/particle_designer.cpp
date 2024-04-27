#define _GLIBCXX_USE_CXX11_ABI 0
#include <raylib-cpp.hpp>
#include <entt/entt.hpp>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "rlgl.h"
#include "Components.hpp"
#include "Systems.hpp"
#include "Game.hpp"

#include <entt/entt.hpp>
#include <entt/entity/snapshot.hpp>

#include <cereal/archives/binary.hpp>
#include <cereal/types/string.hpp>
#include <fstream>

#include <utils/utils.hpp>

#include "utils/TextureCache.hpp"



class DummyGame: public Game {

    public:

        DummyGame() {

            

        }

        void run() {

            update(GetFrameTime());
            this->render();

        }

        void render() {

            auto view = this->getRegistry().view<Renderable, Position, Size>();

            for (auto entity : view) {

                auto& renderable = view.get<Renderable>(entity);
                auto& position = view.get<Position>(entity);
                auto& size = view.get<Size>(entity);

                DrawTexture(renderable.texture, position.position.x, position.position.y, renderable.color);

            }

        }

        void update(double dt) {

            std::vector<std::function<void(Game* game, double dt)>> systems = this->getSystems();

            for (auto system : systems) {

                system(this, dt);

            }

        }

};

int main () {

    raylib::Window w(800, 600, "Particle Designer");

    DummyGame game = DummyGame();
    entt::registry& registry = game.getRegistry();

    game.registerSystem(&particleSystem);
    game.registerSystem(&physicsSystem);

    bool particleSystemDesigner = false;

    SetTargetFPS(60);
    Color color = { 255, 0, 0, 255 };
    float random_scale_x = 0;
    float random_scale_y = 0;
    float gravity_x = 0;
    float gravity_y = 0;
    float life_time = 10;
    char* texture_path = new char[256];

    // Set are default texture
    strcpy(texture_path, "assets/particles/particle.png");

    entt::entity particle = registry.create();
    registry.emplace<Position>(particle, raylib::Vector2(400, 300));
    registry.emplace<Velocity>(particle, raylib::Vector2(0, 0));
    registry.emplace<Size>(particle, raylib::Vector2(32, 32));
    registry.emplace<Particle>(particle, raylib::Vector2(gravity_x, gravity_y), raylib::Vector2(random_scale_x, random_scale_y),
        life_time);
    registry.emplace<Renderable>(particle, LoadTextureCached(texture_path), color);

    // If the particle_designer.particle file exists, we load it
    if (std::ifstream("particle_designer.particle")) {

        std::ifstream file("particle_designer.particle", std::ios::binary);
        cereal::BinaryInputArchive archive(file);

        entt::snapshot_loader{registry}
            .get<Particle>(archive)
            .get<Renderable>(archive);

    }

    auto& renderable = registry.get<Renderable>(particle);
    auto& particle_component = registry.get<Particle>(particle);

    while (!w.ShouldClose()) {

        w.BeginDrawing();
        w.ClearBackground(RAYWHITE);

        // Draw a grid
        for (int i = 0; i < GetScreenWidth(); i += 10) {
            for (int j = 0; j < GetScreenHeight(); j += 10) {
                DrawRectangleLines(i, j, 10, 10, LIGHTGRAY);
            }
        }

        GuiWindowBox((Rectangle){ GetRenderWidth() - 200, 0, 200, GetRenderHeight() }, "Particle Designer");
        GuiColorPicker((Rectangle){ GetRenderWidth() - 190, 40, 150, 180 }, "Color", &color);
        GuiSliderBar((Rectangle){ GetRenderWidth() - 190, 250, 180, 20 }, TextFormat("Scale X: %.2f", random_scale_x), NULL, &random_scale_x, 0.0, 100.0);
        GuiSliderBar((Rectangle){ GetRenderWidth() - 190, 280, 180, 20 }, TextFormat("Scale Y: %.2f", random_scale_y), NULL, &random_scale_y, 0.0, 100.0);
        GuiTextBox((Rectangle){ GetRenderWidth() - 190, 310, 180, 20 }, texture_path, 256, true);
        GuiSliderBar((Rectangle){ GetRenderWidth() - 190, 340, 180, 20 }, TextFormat("Gravity X: %.2f", gravity_x), NULL, &gravity_x, -100.0, 100.0);
        GuiSliderBar((Rectangle){ GetRenderWidth() - 190, 370, 180, 20 }, TextFormat("Gravity Y: %.2f", gravity_y), NULL, &gravity_y, -100.0, 100.0);
        GuiSliderBar((Rectangle){ GetRenderWidth() - 190, 400, 180, 20 }, TextFormat("Life Time: %.2f", life_time), NULL, &life_time, 0.0, 100.0);

        if (registry.valid(particle)) {

            game.run();

        }
        else {

            // Replace the particle
            particle = registry.create();
            registry.emplace<Position>(particle, raylib::Vector2(400, 300));
            registry.emplace<Velocity>(particle, raylib::Vector2(0, 0));
            
            registry.emplace<Size>(particle, raylib::Vector2(32, 32));
            registry.emplace<Particle>(particle, raylib::Vector2(gravity_x, gravity_y), raylib::Vector2(random_scale_x, random_scale_y),
                life_time);

            registry.emplace<Renderable>(particle, LoadTextureCached(texture_path), color);

            renderable = registry.get<Renderable>(particle);
            particle_component = registry.get<Particle>(particle);

        }

        if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_S)) {

            // Save the particle

            std::ofstream file("particle_designer.particle", std::ios::binary);
            cereal::BinaryOutputArchive archive(file);

            entt::snapshot{registry}
                .get<Particle>(archive)
                .get<Renderable>(archive); 



        }

        w.EndDrawing();

    }

    return 0;

}