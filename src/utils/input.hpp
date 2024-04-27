
#pragma once
#include <raylib-cpp.hpp>

enum InputAction { 
    INTERACT, // TODO: Add more actions
    ATTACK,
    AIM
};

raylib::Vector2 getMovementVector(int gamepad) {

    raylib::Vector2 movement = raylib::Vector2(0, 0);

    if (gamepad == -1) {

        if (IsKeyDown(KEY_W)) movement.y -= 1; // TODO: Create a key map / joystick map
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

raylib::Vector2 getAimVector(int gamepad) {

    raylib::Vector2 aim = raylib::Vector2(0, 0);

    if (gamepad == -1) {

        aim = (raylib::Vector2)GetMousePosition() - raylib::Vector2{GetRenderWidth() / 2, GetRenderHeight() / 2}; // TODO: Create a key map / joystick map
        aim = aim.Normalize();

    }

    if (IsGamepadAvailable(gamepad)) {

        aim.x = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X);
        aim.y = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y);

    }
    else {

        TraceLog(LOG_WARNING, "Gamepad %i not available", gamepad);

    }

    return aim;

}

bool isActionDown(int gamepad, InputAction action) {

    if (gamepad == -1) {

        if (action == INTERACT) return IsKeyPressed(KEY_E); // TODO: Create a key map / joystick map
        if (action == ATTACK) return IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    }

    if (IsGamepadAvailable(gamepad)) {

        if (action == INTERACT) return IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
        if (action == ATTACK) return IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT);

    }
    else {

        TraceLog(LOG_WARNING, "Gamepad %i not available", gamepad);

    }

    return false;

}

bool isActionPressed(int gamepad, InputAction action) {

    if (gamepad == -1) {

        if (action == INTERACT) return IsKeyPressed(KEY_E); // TODO: Create a key map / joystick map
        if (action == ATTACK) return IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    }

    if (IsGamepadAvailable(gamepad)) {

        if (action == INTERACT) return IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
        if (action == ATTACK) return IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT);

    }
    else {

        TraceLog(LOG_WARNING, "Gamepad %i not available", gamepad);

    }

    return false;

}

CastDirection getCastDirection(int gamepad) {

    if (gamepad == -1) {

        if (IsKeyPressed(KEY_UP)) return CastDirection::UP; // TODO: Create a key map / joystick map
        if (IsKeyPressed(KEY_DOWN)) return CastDirection::DOWN;
        if (IsKeyPressed(KEY_LEFT)) return CastDirection::LEFT;
        if (IsKeyPressed(KEY_RIGHT)) return CastDirection::RIGHT;

    }

    if (IsGamepadAvailable(gamepad)) {
        
        if (IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_LEFT_FACE_UP)) return CastDirection::UP;
        if (IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_LEFT_FACE_DOWN)) return CastDirection::DOWN;
        if (IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) return CastDirection::LEFT;
        if (IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) return CastDirection::RIGHT;

    }
    else {

        TraceLog(LOG_WARNING, "Gamepad %i not available", gamepad);

    }

    return CastDirection::NONE;

}