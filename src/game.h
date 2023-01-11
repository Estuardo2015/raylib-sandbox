#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "string"
#include "utils.h"
#include "world.h"
#include "block.h"

class Game {
    Player player;
    World world;

public:
    Game();
    void Update();
    void Draw();
    void DrawWorld();
};

Game::Game() {
    player = Player();
    world = NewTestWorld();
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

    DrawWorld();

    EndMode3D();

    DrawFPS(10, 10);

    std::string cameraAngle = "CameraX: " + std::to_string(player.camera.target.x) + " - CameraY: " + std::to_string(player.camera.target.y) + " - Camera Z: " + std::to_string(player.camera.target.z);
    DrawText(StrToCharArr(cameraAngle), 10, 30, 20, BLACK);

    std::string cameraPosition = "CameraPosX: " + std::to_string(player.camera.position.x) + " - CameraPosY: " + std::to_string(player.camera.position.z);
    DrawText(StrToCharArr(cameraPosition), 10, 60, 20, BLUE);

    EndDrawing();
}

void Game::DrawWorld() {
    for (auto c : world.chunks) {
        for (float x = 0; x < 16; ++x) {
            for (float y = 0; y < 16; ++y) {
                for (float z = 0; z < 16; ++z) {
                    int idx = GetIndex({x, y, z}, 16, 16);
                    Block block = c.blocks[idx];
                    DrawCube({ x*1, y*1, z*1 }, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, BLOCK_DICT[block.Material]);
                }
            }
        }
    }
}

#endif