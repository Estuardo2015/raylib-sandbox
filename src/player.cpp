#include "../include/raylib.h"
#include "../include/raymath.h"
#include "player.hpp"
#include <iostream>
#include <math.h>

const float MOUSE_SENSITIVITY = 0.003f;

Player::Player() {
    position = (Vector3){ 4.0f, 0.5f, 4.0f };
    direction = (Vector3){ 0.0f, 1.0f, 0.0f };
    oldMousePosition = (Vector2){0.0f, 0.0f};

    // Define the camera to look into our 3d world
    camera = { 0 };
    camera.position = position;  // Camera position
    camera.target = direction;    // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };        // Camera up vector (rotation towards target)
    camera.fovy = 60.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type
    SetCameraMode(camera, CAMERA_CUSTOM); // Set a first person camera mode
    DisableCursor();
}

void Player::Update() {
    // Handle camera movement
    Vector2 mousePositionDelta = { 0.0f, 0.0f };
    Vector2 mousePos = GetMousePosition();

    mousePositionDelta.x = mousePos.x - oldMousePosition.x;
    mousePositionDelta.y = mousePos.y - oldMousePosition.y;

    oldMousePosition = GetMousePosition();

    camera.target.x -= (mousePositionDelta.x * -MOUSE_SENSITIVITY);
    camera.target.y += (mousePositionDelta.y * -MOUSE_SENSITIVITY);

    //Handle keys & mouse
    //Calculate direction vectors of the camera angle
//    float cx = cosf(camera.target.x);
//    float sx = sinf(camera.target.x);
//
//    float cx90 = cosf(camera.target.x + PI / 2);
//    float sx90 = sinf(camera.target.x + PI / 2);
//
//    Vector3 moveDir = { 0 };
//
//    if (IsKeyDown(KEY_W)) {
//        moveDir.z += sx;
//        moveDir.x += cx;
//    }
//
//    if (IsKeyDown(KEY_S)) {
//        moveDir.z -= sx;
//        moveDir.x -= cx;
//    }
//
//    if (IsKeyDown(KEY_A)) {
//        moveDir.z -= sx90;
//        moveDir.x -= cx90;
//    }
//
//    if (IsKeyDown(KEY_D)) {
//        moveDir.z += sx90;
//        moveDir.x += cx90;
//    }
//
//    moveDir = Vector3ClampValue(moveDir, 0.0f, 1.0f);
//
//    camera.position.z += moveDir.z;
//    camera.position.x += moveDir.x;

    UpdateCamera(&camera);
}
