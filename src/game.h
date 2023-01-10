#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "string"
#include "utils.h"

class Game {
    Player player;

public:
    Game();
    void Update();
    void Draw();
};

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
    DrawText(StrToCharArr(cameraAngle), 10, 30, 20, BLACK);

    std::string cameraPosition = "CameraPosX: " + std::to_string(player.camera.position.x) + " - CameraPosY: " + std::to_string(player.camera.position.z);
    DrawText(StrToCharArr(cameraPosition), 10, 60, 20, BLUE);

    EndDrawing();
}

#endif