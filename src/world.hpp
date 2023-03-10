#ifndef WORLD_HPP
#define WORLD_HPP

#include "block.hpp"
#include "chunk.hpp"
#include "../include/PerlinNoise.hpp"
#include <unordered_map>
#include <string>
#include "blockDataManager.hpp"

const int WORLD_WIDTH = 16; // In chunks

class World {
public:
    float noiseScale = 0.03;
    int waterThreshold = 1;
    std::vector<std::vector<Chunk>> chunkMap;

    World();

    void GenerateWorld();

    void GenerateTerrain(siv::PerlinNoise, Chunk *chunk);

    void GenerateTestBlocks(Chunk *chunk);

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
            GenerateTerrain(perlin, &chunk);
            chunkMap[x].push_back(chunk);
        }
    }
}

void World::GenerateTerrain(siv::PerlinNoise perlin, Chunk *chunk) {
    for (float x = 0; x < CHUNK_WIDTH; x++) {
        for (float z = 0; z < CHUNK_WIDTH; z++) {
            for (float y = 0; y < CHUNK_HEIGHT; y++) {
                double noiseValue = perlin.noise3D(((CHUNK_WIDTH * chunk->worldPosition.x) + x) * noiseScale, (0 + y) * noiseScale, ((CHUNK_WIDTH * chunk->worldPosition.y) + z) * noiseScale);
                //float noiseValue = Mathf.PerlinNoise((chunk.worldPosition.x + x) * noiseScale, (chunk.worldPosition.z + z) * noiseScale);
                int groundPosition = std::round(noiseValue * CHUNK_HEIGHT);

                BlockType blockType = Dirt;
                if (y > groundPosition) {
                    if (y < waterThreshold) {
                        blockType = Water;
                    } else {
                        blockType = Air;
                    }
                } else if (y == groundPosition) {
                    blockType = Grass;
                }

                chunk->SetBlock({x, y, z}, Block(blockType));
            }
        }
    }
}

void World::GenerateTestBlocks(Chunk *chunk) {
    for (float x = 0; x < CHUNK_WIDTH; ++x) {
        for (float z = 0; z < CHUNK_WIDTH; ++z) {
            chunk->SetBlock({x, 0, z}, Block(Grass));

        }
    }
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