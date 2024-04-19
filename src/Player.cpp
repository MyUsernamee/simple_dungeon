#include "Player.hpp"
#include "Components.hpp"

void playerSystem(entt::registry &registry)
{

    auto view = registry.view<Player, Velocity>();
    bool* player_exists = new bool[4]; // TODO: Make this more efficient and make it a constant / variable

    for (int i = 0; i < 4; i++)
    {
        player_exists[i] = false;
    }

    for (auto entity : view)
    {
        auto &player = view.get<Player>(entity);
        auto &velocity = view.get<Velocity>(entity);

        raylib::Vector2 movement = getMovementVector(player.gamepad);
        velocity.velocity = movement * 100.0; // TODO: Make this a constant / variable

        player_exists[player.gamepad + 1] = true;
        
    }

    // We listen for either the keyboard or the gamepad
    // If a player with the corresponding gamepad is not found we create a new player
    for (int i = -1; i < 3; i++)
    {

        if (!player_exists[i + 1] && ((i == -1 && IsKeyDown(KEY_SPACE)) || (i != -1 && IsGamepadButtonPressed(i, GAMEPAD_BUTTON_RIGHT_FACE_DOWN))))
        {
            createPlayer(registry, raylib::Color(GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255), i);
            // WaitTime(0.2);
        }        

    }


}


entt::entity createPlayer(entt::registry &registry, raylib::Color color, int gamepad)
{
    auto player = registry.create();
    auto& renderable_player = registry.emplace<renderable>(player);

    renderable_player.renderer = new PlayerRenderer(color);
    renderable_player.z = 0;

    registry.emplace<Position>(player, raylib::Vector2(200, 100));
    registry.emplace<Velocity>(player, raylib::Vector2(0, 0));
    registry.emplace<Size>(player, raylib::Vector2(32, 32));
    registry.emplace<Collision>(player, 0b1);
    registry.emplace<Player>(player, raylib::Color(255, 0, 0, 255), gamepad);
    registry.emplace<CameraFollower>(player, 1, raylib::Vector2(25, 25));

    return player;
}

raylib::Vector2 getMovementVector(int gamepad) {

    raylib::Vector2 movement = raylib::Vector2(0, 0);

    if (gamepad == -1) {

        if (IsKeyDown(KEY_W)) movement.y -= 1;
        if (IsKeyDown(KEY_S)) movement.y += 1;
        if (IsKeyDown(KEY_A)) movement.x -= 1;
        if (IsKeyDown(KEY_D)) movement.x += 1;

        return movement;

    }

    if (IsGamepadAvailable(gamepad)) {

        movement.x = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X);
        movement.y = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y);

    }
    else {

        TraceLog(LOG_WARNING, "Gamepad %i not available", gamepad);

    }

    return movement;

}

PlayerRenderer::PlayerRenderer(raylib::Color color)
{

    this->color = color;
    this->idleAnimation = Animation("assets/0x72_DungeonTilesetII_v1.7/frames/skelet_idle_anim_f%d.png");
    this->runAnimation = Animation("assets/0x72_DungeonTilesetII_v1.7/frames/skelet_run_anim_f%d.png");

}

void PlayerRenderer::render(const entt::registry &registry, const entt::entity &entity)
{

    auto &transform = registry.get<Position>(entity);
    auto &player = registry.get<Player>(entity);
    auto &velocity = registry.get<Velocity>(entity);
    
    Texture2D frame;

    if (velocity.velocity.LengthSqr() > 0) {

        frame = runAnimation.getFrame((int)(GetTime() * 12.0) % runAnimation.getFrameCount()); // TODO: Make this a constant / variable

    }
    else {

        frame = idleAnimation.getFrame((int)(GetTime() * 4.0) % idleAnimation.getFrameCount());

    }

    bool flip = velocity.velocity.x < 0;

    if (flip) {

        DrawTexturePro(
            frame,
            Rectangle{0, 0, -(float)frame.width, (float)frame.height},
            Rectangle{transform.position.x, transform.position.y, (float)frame.width * 2, (float)frame.height * 2},
            raylib::Vector2(0, 0),
            0,
            color
        );
    }
    else {

        DrawTextureEx(frame, raylib::Vector2(transform.position.x, transform.position.y), 0, 2, color);

    }

}
