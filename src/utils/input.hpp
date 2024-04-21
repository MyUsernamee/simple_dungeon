
#pragma once
#include <raylib-cpp.hpp>

enum InputAction { 
    INTERACT, // TODO: Add more actions
    ATTACK,
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

bool isActionDown(int gamepad, InputAction action) {

    if (gamepad == -1) {

        if (action == INTERACT) return IsKeyDown(KEY_E); // TODO: Create a key map / joystick map
        if (action == ATTACK) return IsMouseButtonDown(MOUSE_LEFT_BUTTON);

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

        if (action == INTERACT) return IsKeyDown(KEY_E); // TODO: Create a key map / joystick map
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