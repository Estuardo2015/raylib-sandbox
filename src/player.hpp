#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <cmath>

const float MOUSE_SENSITIVITY = 0.003f;

class Player {
    Vector3 position;
    Vector3 direction;
    Vector3 velocity;
    float speed;
    CameraMode cameraMode;

public:
    Vector2 oldMousePosition;
    Camera3D camera{};

    void Update();
    Player(CameraMode cm);
    Player();
};

Player::Player(CameraMode cm) {
    // Initialize player state
    position = (Vector3){ 4.0f, 0.5f, 4.0f };
    direction = (Vector3){ 0.0f, 1.0f, 0.0f };
    velocity = (Vector3){ 0.0f, 0.0f, 0.0f };
    speed = 0.125f / 20;
    oldMousePosition = (Vector2){0.0f, 1.0f};

    // Define the camera to look into our 3d world
    camera = { 0 };
    camera.position = position;  // Camera position
    camera.target = direction;    // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };        // Camera up vector (rotation towards target)
    camera.fovy = 60.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type
    cameraMode = cm;
    SetCameraMode(camera, cameraMode); // Set a first person camera mode
    DisableCursor();
}

Player::Player() {

}

void Player::Update() {
    if (cameraMode == CAMERA_CUSTOM) {
        // Handle camera movement
        Vector2 mousePositionDelta = { 0.0f, 0.0f };
        Vector2 mousePos = GetMousePosition();

        mousePositionDelta.x = mousePos.x - oldMousePosition.x;
        mousePositionDelta.y = mousePos.y - oldMousePosition.y;

        oldMousePosition = GetMousePosition();

        direction.x -= (mousePositionDelta.x * -MOUSE_SENSITIVITY);
        direction.y -= (mousePositionDelta.y * -MOUSE_SENSITIVITY);

        // Calculate direction vectors of the camera angle
        float cx = cosf(direction.x);
        float sx = sinf(direction.x);

        float cx90 = cosf(direction.x + PI / 2);
        float sx90 = sinf(direction.x + PI / 2);

        float sy = sinf(direction.y);
        float cy = cosf(direction.y);

        float forwardX = cx * sy;
        float forwardY = cy;
        float forwardZ = sx * sy;

        // Handle keys & mouse
        Vector3 moveDir = { 0 };
        if (IsKeyDown(KEY_W)) {
            moveDir.z += sx;
            moveDir.x += cx;
        }

        if (IsKeyDown(KEY_S)) {
            moveDir.z -= sx;
            moveDir.x -= cx;
        }

        if (IsKeyDown(KEY_A)) {
            moveDir.z -= sx90;
            moveDir.x -= cx90;
        }

        if (IsKeyDown(KEY_D)) {
            moveDir.z += sx90;
            moveDir.x += cx90;
        }

        moveDir = Vector3ClampValue(moveDir, 0.0f, 1.0f);
        Vector3 moveVel = Vector3Scale(moveDir, speed);
        velocity = Vector3Add(velocity, moveVel);

        // Place camera's target to the direction looking at.
        camera.target.x = camera.position.x + forwardX;
        camera.target.y = camera.position.y + forwardY;
        camera.target.z = camera.position.z + forwardZ;

        // Calculate velocity with delta time
        Vector3 velXdt = Vector3Scale(velocity, GetFrameTime() * 60);

        int steps = 8;

        for (int i = 0; i < steps; i++) {
            position.x += velXdt.x / steps;
        }

        for (int i = 0; i < steps; i++) {
            position.y += velXdt.y / steps;
        }

        for (int i = 0; i < steps; i++) {
            position.z += velXdt.z / steps;
        }

        velocity.x -= velocity.x / 6.0f;
        velocity.z -= velocity.z / 6.0f;

        camera.position = position;
    }

    UpdateCamera(&camera);
}

#endif