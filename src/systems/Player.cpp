
#include "Components.hpp"
#include "Constructors.hpp"
#include "utils/consts.hpp"

#include "utils/input.hpp"
#include <data/Dungeon.hpp>
#include "Game.hpp"
#include <algorithm>

void playerSystem(Game* game, double dt)
{

    auto &registry = game->getRegistry();

    auto view = registry.view<Player, Velocity, Position, SpellCaster, Size>();
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
        auto &size = view.get<Size>(entity);

        // Calculate the center
        auto center = raylib::Vector2(position.position.x + size.size.x / 2, position.position.y + size.size.y / 2);

        // Get the cursor entity
        auto cursor = registry.get<Player>(entity).cursorEntity;
        auto &cursorPosition = registry.get<Position>(cursor);
        auto &cursorRenderable = registry.get<Renderable>(cursor);

        raylib::Vector2 movement = getMovementVector(player.gamepad);
        velocity.velocity = movement * 100.0; // TODO: Make this a constant / variable

        raylib::Vector2 aim = getAimVector(player.gamepad);
        cursorPosition.position = center + aim * 100.0; // TODO: Make this a constant / variable

        cursorRenderable.opacity = 255 * std::min(aim.Length(), 1.0f);

        if (isActionPressed(player.gamepad, ATTACK))
        {
            spellCaster.cast(game, entity, aim);
        }

        CastDirection castDirection = getCastDirection(player.gamepad);

        if (castDirection != CastDirection::NONE)
        {
            spellCaster.addCastDirection(registry, position.position, castDirection);
            SetGamepadVibration(player.gamepad, 0.25 * spellCaster.currentCastDirections.size(), 0.25 * spellCaster.currentCastDirections.size());
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

