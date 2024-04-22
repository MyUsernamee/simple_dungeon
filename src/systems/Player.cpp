
#include "Components.hpp"
#include "Constructors.hpp"
#include "utils/consts.hpp"

#include "utils/input.hpp"

void playerSystem(entt::registry &registry)
{

    auto view = registry.view<Player, Velocity, Position, SpellCaster>();
    bool* player_exists = new bool[4]; // TODO: Make this more efficient and make it a constant / variable

    for (int i = 0; i < 4; i++)
    {
        player_exists[i] = false;
    }

    for (auto entity : view)
    {
        auto &player = view.get<Player>(entity);
        auto &position = view.get<Position>(entity);
        auto &velocity = view.get<Velocity>(entity);
        auto &spellCaster = view.get<SpellCaster>(entity);

        raylib::Vector2 movement = getMovementVector(player.gamepad);
        velocity.velocity = movement * 100.0; // TODO: Make this a constant / variable

        if (isActionPressed(player.gamepad, ATTACK))
        {
            createProjectile(registry, position.position + movement.Normalize() * 40, movement, 500, 10);
        }

        CastDirection castDirection = getCastDirection(player.gamepad);

        if (castDirection != CastDirection::NONE)
        {
            spellCaster.addCastDirection(registry, position.position, castDirection);
        }

        player_exists[player.gamepad + 1] = true;
        
    }

    // We listen for either the keyboard or the gamepad
    // If a player with the corresponding gamepad is not found we create a new player
    for (int i = -1; i < 3; i++)
    {

        if (!player_exists[i + 1] && ((i == -1 && IsKeyDown(KEY_SPACE)) || (i != -1 && IsGamepadButtonPressed(i, GAMEPAD_BUTTON_RIGHT_FACE_DOWN))))
        {
            createPlayer(registry, raylib::Color(GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255), i, raylib::Vector2(128, 128) * TILE_SIZE);
            // WaitTime(0.2);
        }        

    }

}

