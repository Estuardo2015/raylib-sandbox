#ifndef GAME_HPP
#define GAME_HPP

#include "player.hpp"
#include "string"
#include "utils.hpp"
#include "world.hpp"
#include "block.hpp"
#include "blockDataManager.hpp"

class Game {

public:
    Game();

    void Update();

    void Draw();

    Player player;
    World world;
};

Game::Game() {
    blockDataManager = new BlockDataManager();

    player = Player(CAMERA_FREE);
    world = World();
}

void Game::Update() {
    player.Update();

    if (IsKeyPressed(KEY_SPACE)) {
        world.GenerateWorld();
    }

    world.Update();
}

void Game::Draw() {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    BeginMode3D(player.camera);

    DrawGrid(50, 1.0f);

    world.Render();

    EndMode3D();

    DrawFPS(10, 10);

    EndDrawing();
}

#endif