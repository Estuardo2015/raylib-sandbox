#include "game.hpp"
#include "string"
#include "cstring"
#include "utils.h"

Game::Game() {
    player = Player();
}

void Game::Update() {
    player.Update();
}

void Game::Draw() {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    BeginMode3D(player.camera);

    DrawPlane((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector2){ 32.0f, 32.0f }, LIGHTGRAY); // Draw ground

    DrawCube({ 0.0f, 0.0f, 0.0f }, 2.0f, 2.0f, 2.0f, RED);
    DrawCubeWires({ 0.0f, 0.0f, 0.0f }, 2.0f, 2.0f, 2.0f, MAROON);

    DrawGrid(10, 1.0f);

    EndMode3D();

    DrawFPS(10, 10);

    std::string cameraAngle = "CameraX: " + std::to_string(player.camera.target.x) + " - CameraY: " + std::to_string(player.camera.target.y) + " - Camera Z: " + std::to_string(player.camera.target.z);
    DrawText(StrToCharArr(cameraAngle), 10, 25, 20, LIGHTGRAY);

    std::string cameraPosition = "CameraX: " + std::to_string(player.camera.position.x) + " - CameraY: " + std::to_string(player.camera.position.z);
    DrawText(StrToCharArr(cameraPosition), 10, 50, 20, BLUE);

    EndDrawing();
}