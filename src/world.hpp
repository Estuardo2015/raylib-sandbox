#ifndef WORLD_HPP
#define WORLD_HPP

#include "block.hpp"
#include "chunk.hpp"
#include "../include/PerlinNoise.hpp"
#include <unordered_map>
#include <string>
#include "blockDataManager.hpp"
#include "threadPool.hpp"

const int WORLD_WIDTH = 24; // In chunks
const int WORLD_GENERATION_NUM_THREADS = 16;
const int WORLD_UPDATE_NUM_THREADS = 16;

ThreadPool worldGenerationThreadPool = ThreadPool(WORLD_GENERATION_NUM_THREADS);
ThreadPool worldUpdateThreadPool = ThreadPool(WORLD_UPDATE_NUM_THREADS);

class World {
public:
    float noiseScale = 0.015;
    int waterThreshold = 1;
    std::vector<std::vector<Chunk>> chunkMap;

    World();

    void GenerateWorld();

    void Update();

    void Render();
};

World::World() {
    GenerateWorld();
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

    for (int x = 0; x < WORLD_WIDTH; x++) {
        for (int y = 0; y < WORLD_WIDTH; y++) {
            worldGenerationThreadPool.QueueJob([this, x, y, perlin] {
                chunkMap[x][y].GenerateTerrain(perlin, noiseScale, waterThreshold);
            });
        }
    }

    worldGenerationThreadPool.WaitUntilFinished();
}

void World::Update() {
    for (int x = 0; x < WORLD_WIDTH; x++) {
        for (int z = 0; z < WORLD_WIDTH; z++) {
            worldUpdateThreadPool.QueueJob([this, x, z] {
                chunkMap[x][z].Update(&chunkMap, WORLD_WIDTH);
            });
        }
    }

    worldUpdateThreadPool.WaitUntilFinished();
}

void World::Render() {
    for (int x = 0; x < WORLD_WIDTH; x++) {
        for (int z = 0; z < WORLD_WIDTH; z++) {
            chunkMap[x][z].Render();
        }
    }
}

#endif