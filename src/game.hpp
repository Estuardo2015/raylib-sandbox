#ifndef GAME_HPP
#define GAME_HPP

#include "player.hpp"
#include "string"
#include "utils.hpp"
#include "world.hpp"
#include "block.hpp"
#include "blockDataManager.hpp"

class Game {
    World world;

public:
    Game();
    void Update();
    void Draw();

    Player player;
};

Game::Game() {
    player = Player(CAMERA_FREE);
    world = World();
    world.GenerateWorld();
    blockDataManager = new BlockDataManager();
}

void Game::Update() {
    player.Update();
}

void Game::Draw() {
//    BeginDrawing();
//
//    ClearBackground(RAYWHITE);
//
//    BeginMode3D(player.camera);
//
//    DrawPlane((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector2){ 32.0f, 32.0f }, LIGHTGRAY); // Draw ground
//
//    DrawGrid(10, 1.0f);
//
//    world.Render();
//
//    EndMode3D();
//
//    DrawFPS(10, 10);
//
//    std::string cameraAngle = "CameraX: " + std::to_string(player.camera.target.x) + " - CameraY: " + std::to_string(player.camera.target.y) + " - Camera Z: " + std::to_string(player.camera.target.z);
//    DrawText(StrToCharArr(cameraAngle), 10, 30, 20, BLACK);
//
//    std::string cameraPosition = "CameraPosX: " + std::to_string(player.camera.position.x) + " - CameraPosY: " + std::to_string(player.camera.position.z);
//    DrawText(StrToCharArr(cameraPosition), 10, 60, 20, BLUE);
//
//    EndDrawing();
}

#endif