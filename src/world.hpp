#ifndef WORLD_HPP
#define WORLD_HPP

#include "block.hpp"
#include "chunk.hpp"
#include "../include/PerlinNoise.hpp"
#include <unordered_map>
#include <string>
#include "blockDataManager.hpp"

const int WORLD_WIDTH = 1; // In chunks

class World {
public:
    float noiseScale = 0.03;
    int waterThreshold = 50;
    Chunk chunkMap[WORLD_WIDTH][WORLD_WIDTH];

    World();

    void GenerateWorld();

    void GenerateBlocks(Chunk *chunk);

    void Render();
};

World::World() {

}

void World::GenerateWorld() {
    for (int x = 0; x < WORLD_WIDTH; x++) {
        for (int y = 0; y < WORLD_WIDTH; y++) {
            Chunk chunk = Chunk({float(x), float(y)});
            GenerateBlocks(&chunk);
            chunkMap[x][y] = chunk;
        }
    }
}

void World::GenerateBlocks(Chunk *chunk) {
    for (float x = 0; x < CHUNK_WIDTH; x++) {
        for (float z = 0; z < CHUNK_WIDTH; z++) {
            siv::PerlinNoise perlin{};

            double noiseValue = perlin.noise2D((chunk->worldPosition.x + x) * noiseScale, (0 + z) * noiseScale);
            //float noiseValue = Mathf.PerlinNoise((chunk.worldPosition.x + x) * noiseScale, (chunk.worldPosition.z + z) * noiseScale);
            int groundPosition = std::round(noiseValue * CHUNK_HEIGHT);

            for (float y = 0; y < CHUNK_HEIGHT; y++) {
                BlockType blockType = Dirt;
                if (y > groundPosition) {
//                    if (y < waterThreshold) {
//                        blockType = Water;
//                    } else {
//                        blockType = Air;
//                    }
                    blockType = Air;
                } else if (y == groundPosition) {
                    blockType = Grass;
                }

                chunk->SetBlock({x, y, z}, Block(blockType));
            }
        }
    }
}

void World::Render() {
    for (int x = 0; x < WORLD_WIDTH; x++) {
        for (int z = 0; z < WORLD_WIDTH; z++) {
            Chunk chunk = chunkMap[x][z];
            chunk.Render(x, z);
        }
    }
}

#endif