#include "Game.hpp"
#include <entt/entt.hpp>
#include <raylib-cpp.hpp>
#include "Systems.hpp"
#include "Components.hpp"
#include "Constructors.hpp"
//#define DEBUG

Game::Game()
{

    // Initialize the camera
    camera = raylib::Camera2D(raylib::Vector2(GetRenderWidth() / 2, GetRenderHeight() / 2), raylib::Vector2(GetRenderWidth() / 2, GetRenderHeight() / 2), 0.0f, 1.0f);
    registry = entt::registry();
    lightShader = LoadShader(NULL, "assets/shaders/lighting.fs");

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

    loadSpells(this);
    target = LoadRenderTexture(GetRenderWidth(), GetRenderHeight());
    lightTarget = LoadRenderTexture(GetRenderWidth(), GetRenderHeight());

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


    std::vector<std::pair<raylib::Vector2, Light>> lights;

    // We get all lights
    auto _view = registry.view<Light, Position>();

    for (auto entity : _view) {

        auto& position = _view.get<Position>(entity);
        auto& light = _view.get<Light>(entity);

        lights.push_back({position.position, light});

    }

    camera.BeginMode();

    // Get the dungeon
    auto dungeon = getDungeon();
    dungeon.render(camera);
    
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
            raylib::Color{Renderable_.color.r, Renderable_.color.g, Renderable_.color.b, Renderable_.opacity}
        );

        #ifdef DEBUG
        DrawRectangleLines(Position_.position.x - Size_.size.x / 2, Position_.position.y - Size_.size.y / 2, Size_.size.x, Size_.size.y, raylib::Color(255, 0, 0, 255));
        #endif

    }

    // Draw the texture again over the bloom
    //DrawTextureRec(target.texture, raylib::Rectangle{0, 0, target.texture.width, -target.texture.height}, raylib::Vector2{0, 0}, raylib::Color{255, 255, 255, 255});


    camera.EndMode();

    // Now we render the lights
    BeginTextureMode(lightTarget);
    ClearBackground(raylib::Color(50, 50, 50, 255));
    camera.BeginMode();
    BeginBlendMode(BLEND_ADDITIVE);

    dungeon.renderLighting(camera, lights);

    // Render glow entities
    auto glowView = registry.view<Renderable, Position, Size, Glow>();

    

    for (auto entity : glowView) {

        auto& Renderable_ = glowView.get<Renderable>(entity);
        auto& Position_ = glowView.get<Position>(entity);
        auto& Size_ = glowView.get<Size>(entity);
        auto& Glow_ = glowView.get<Glow>(entity);

        DrawCircleGradient(Position_.position.x, Position_.position.y, Glow_.radius, Renderable_.color, raylib::Color{0, 0, 0, 0});

    }

    EndBlendMode();
    camera.EndMode();
    EndTextureMode();

    BeginBlendMode(BLEND_MULTIPLIED);
    DrawTextureRec(lightTarget.texture, raylib::Rectangle{0, 0, lightTarget.texture.width, -lightTarget.texture.height}, raylib::Vector2{0, 0}, raylib::Color{255, 255, 255, 255});
    EndBlendMode();


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

