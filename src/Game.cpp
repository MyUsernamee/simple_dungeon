#include "Game.hpp"
#include <entt/entt.hpp>
#include <raylib-cpp.hpp>
#include "Systems.hpp"
#include "Components.hpp"
#include "Constructors.hpp"
#include "renderers/SpellCasterRenderer.hpp"
//#define DEBUG

Game::Game()
{

    // Initialize the camera
    camera = raylib::Camera2D(raylib::Vector2(GetRenderWidth() / 2, GetRenderHeight() / 2), raylib::Vector2(GetRenderWidth() / 2, GetRenderHeight() / 2), 0.0f, 1.0f);
    registry = entt::registry();

    // For stress testing lets add a bunch of entities
    // for (int i = 0; i < 200; i++) {

    //     auto entity = registry.create();
    //     auto& Renderable_ = registry.emplace<Renderable>(entity);

    //     Renderable_.renderer = new SquareRenderer(raylib::Color(255, 0, 0, 255));
    //     Renderable_.z = 0;

    //     registry.emplace<Position>(entity, raylib::Vector2(GetRandomValue(0, GetRenderWidth()), GetRandomValue(0, GetRenderHeight())));
    //     registry.emplace<Velocity>(entity, raylib::Vector2(GetRandomValue(-100, 100), GetRandomValue(-100, 100)));
    //     registry.emplace<Size>(entity, raylib::Vector2(50, 50));
    //     registry.emplace<Collision>(entity, 1);

    // }

    // createPlayer(registry, raylib::Color(255, 0, 0, 255), -1);

    spells = loadSpells();

}

Game::~Game()
{

    // Do nothing

}

void Game::run()
{

    update(GetFrameTime());
    render();

}

void Game::render()
{

    camera.BeginMode();


    std::vector<std::pair<raylib::Vector2, double>> visibility_points;

    // We get all lights
    auto _view = registry.view<Light, Position>();

    for (auto entity : _view) {

        auto& position = _view.get<Position>(entity);
        visibility_points.push_back({position.position, _view.get<Light>(entity).radius});

    }

    // Get the dungeon
    auto dungeon = getDungeon();
    dungeon.render(camera, visibility_points);
    
    // Sort the registry by z-index
    registry.sort<Renderable>([](const Renderable& a, const Renderable& b) {
        return a.z < b.z;
    });

    // We then iterate over all entities with a Renderable component
    auto view = registry.view<Renderable, Position, Size>();

    for (auto entity : view) {

        auto& Renderable_ = view.get<Renderable>(entity);
        auto& Position_ = view.get<Position>(entity);
        auto& Size_ = view.get<Size>(entity);

        // Check if the entity is visible
        raylib::Vector2 screen_position = camera.GetWorldToScreen(Position_.position);
        if (screen_position.x < 0 || screen_position.x > GetRenderWidth() || screen_position.y < 0 || screen_position.y > GetRenderHeight()) continue;

        int flip_x_multiplier = Renderable_.flipX ? -1 : 1;
        int flip_y_multiplier = Renderable_.flipY ? -1 : 1;

        //TraceLog(LOG_INFO, "Rendering entity with z-index %d", Renderable_.z);
        DrawTexturePro(
            Renderable_.texture,
            raylib::Rectangle{0, 0, Renderable_.texture.width * flip_x_multiplier, Renderable_.texture.height * flip_y_multiplier},
            raylib::Rectangle{Position_.position.x - Size_.size.x / 2, Position_.position.y - Size_.size.y / 2, Size_.size.x, Size_.size.y},
            raylib::Vector2{0, 0},
            0.0f,
            Renderable_.color
        );

        #ifdef DEBUG
        DrawRectangleLines(Position_.position.x - Size_.size.x / 2, Position_.position.y - Size_.size.y / 2, Size_.size.x, Size_.size.y, raylib::Color(255, 0, 0, 255));
        #endif

    }

    spellCasterRenderer(registry);

    camera.EndMode();

    // Get everyplayer
    for (auto render_system : renderSystems) {

        render_system(this, GetFrameTime());

    }

}

void Game::update(double dt)
{

    for (auto system : systems) {
        system(this, dt);
    }

    // If the user presses r we spawn an enemy at the mouse position
    if (IsKeyPressed(KEY_R)) {

        Texture particle = LoadTexture("assets/particles/up.png");

        createParticle(registry, camera.GetScreenToWorld(GetMousePosition()), raylib::Vector2(GetRandomValue(-100, 100), GetRandomValue(-100, 100)), particle, {20.0, 20.0}, {0.0, 0.0}, 1.0, RED);

    }
    

}

