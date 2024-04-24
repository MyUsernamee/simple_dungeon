#include "Game.hpp"
#include <entt/entt.hpp>
#include "renderers/SquareRenderer.hpp"
#include <raylib-cpp.hpp>
#include "Systems.hpp"
#include "Components.hpp"
#include "Constructors.hpp"
#include "renderers/PlayerRenderer.hpp"
#include "renderers/SpellCasterRenderer.hpp"

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


    std::vector<raylib::Vector2> visibility_points;

    // We get all players
    auto _view = registry.view<Player, Position>();

    for (auto entity : _view) {

        auto& position = _view.get<Position>(entity);
        visibility_points.push_back(position.position);

    }

    // Get the dungeon
    auto dungeon = getDungeon();
    dungeon.render(camera, visibility_points);
    
    // Sort the registry by z-index
    registry.sort<Renderable>([](const Renderable& a, const Renderable& b) {
        return a.z < b.z;
    });

    // We then iterate over all entities with a Renderable component
    auto view = registry.view<Renderable>();

    for (auto entity : view) {

        auto& Renderable_ = view.get<Renderable>(entity);
        //TraceLog(LOG_INFO, "Rendering entity with z-index %d", Renderable_.z);
        Renderable_.renderer->render(registry, entity);

    }

    spellCasterRenderer(registry);

    camera.EndMode();

    // Get everyplayer
    auto new_view = registry.view<Player, Renderable>();

    for (auto entity : new_view) {

        auto& player = new_view.get<Player>(entity);
        auto& Renderable_ = new_view.get<Renderable>(entity);

        // Convert the renderer to a player renderer
        dynamic_cast<PlayerRenderer*>(Renderable_.renderer)->statsRenderer(registry, entity);

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

