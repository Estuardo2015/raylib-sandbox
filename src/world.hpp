#ifndef WORLD_HPP
#define WORLD_HPP

#include "block.hpp"
#include "chunk.hpp"
#include "../include/PerlinNoise.hpp"
#include <unordered_map>
#include <string>
#include "blockDataManager.hpp"
#include "threadPool.hpp"

const int WORLD_WIDTH = 16; // In chunks

class World {
public:
    float noiseScale = 0.03;
    int waterThreshold = 1;
    std::vector<std::vector<Chunk>> chunkMap;

    World();

    void GenerateWorld();

    void Update();

    void Render();
};

World::World() {

}

void World::GenerateWorld() {
    chunkMap.clear();

    siv::PerlinNoise perlin{ std::random_device{} };
    perlin.reseed(time(0));

    for (int x = 0; x < WORLD_WIDTH; x++) {
        chunkMap.emplace_back();
        for (int y = 0; y < WORLD_WIDTH; y++) {
            Chunk chunk = Chunk({float(x), float(y)});
            chunkMap[x].push_back(chunk);
        }
    }

    ThreadPool worldGenerationThreadPool = ThreadPool(8);
    for (int x = 0; x < WORLD_WIDTH; x++) {
        for (int y = 0; y < WORLD_WIDTH; y++) {
            worldGenerationThreadPool.QueueJob([this, x, y, perlin] {
                chunkMap[x][y].GenerateTerrain(perlin, noiseScale, waterThreshold);
            });
        }
    }

    worldGenerationThreadPool.WaitUntilFinished();
    worldGenerationThreadPool.Stop();
}

void World::Update() {
    for (int x = 0; x < WORLD_WIDTH; x++) {
        for (int z = 0; z < WORLD_WIDTH; z++) {
            chunkMap[x][z].Update(x, z);
        }
    }
}

void World::Render() {
    for (int x = 0; x < WORLD_WIDTH; x++) {
        for (int z = 0; z < WORLD_WIDTH; z++) {
            Chunk chunk = chunkMap[x][z];
            chunk.Render();
        }
    }
}

#endif