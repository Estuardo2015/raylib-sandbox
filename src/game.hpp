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
    world.GenerateWorld();
}

void Game::Update() {
    player.Update();

    world.Update();
}

void Game::Draw() {

}

#endif