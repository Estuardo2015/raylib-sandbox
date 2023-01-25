#ifndef WORLD_HPP
#define WORLD_HPP

#include "block.hpp"
#include "chunk.hpp"
#include "blockDataManager.hpp"
#include "../include/PerlinNoise.hpp"
#include <unordered_map>
#include <string>

const int WORLD_SIZE = 1; // In chunks

class World {
public:
    float noiseScale = 0.03;
    int waterThreshold = 50;
    Chunk chunkMap[WORLD_SIZE][WORLD_SIZE];

    World();

    void GenerateWorld();

    void GenerateBlocks(Chunk chunk);

    void Render();

    void GenerateTestWorld(Chunk *chunk);
};

World::World() {

}

void World::GenerateWorld() {
    for (int x = 0; x < WORLD_SIZE; x++) {
        for (int y = 0; y < WORLD_SIZE; y++) {
            Chunk chunk = Chunk();
            chunk.worldPosition = {float(x), float(y)};
            GenerateTestWorld(&chunk);
            chunkMap[x][y] = chunk;
        }
    }
}

void World::GenerateTestWorld(Chunk *chunk) {
    for (float x = 0; x < CHUNK_WIDTH; x++) {
        for (float z = 0; z < CHUNK_WIDTH; z++) {
            chunk->SetBlock({x, 0, z}, Block(Dirt));
        }
    }
}

void World::GenerateBlocks(Chunk chunk) {
    for (float x = 0; x < CHUNK_WIDTH; x++) {
        for (float z = 0; z < CHUNK_WIDTH; z++) {
            siv::PerlinNoise perlin{};

            double noiseValue = perlin.noise2D((chunk.worldPosition.x + x) * noiseScale, (0 + z) * noiseScale);
            //float noiseValue = Mathf.PerlinNoise((chunk.worldPosition.x + x) * noiseScale, (chunk.worldPosition.z + z) * noiseScale);
            int groundPosition = std::round(noiseValue * CHUNK_HEIGHT);

            for (float y = 0; y < CHUNK_HEIGHT; y++) {
                BlockType blockType = Dirt;
                if (y > groundPosition) {
                    if (y < waterThreshold) {
                        blockType = Water;
                    } else {
                        blockType = Air;
                    }

                } else if (y == groundPosition) {
                    blockType = Grass_Dirt;
                }

                chunk.SetBlock({x, y, z}, Block(blockType));
            }
        }
    }
}

void World::Render() {
    for (int x = 0; x < WORLD_SIZE; x++) {
        for (int y = 0; y < WORLD_SIZE; y++) {
            Chunk chunk = chunkMap[x][y];

            for (int chunkX = 0; chunkX < CHUNK_WIDTH; chunkX++) {
                for (int chunkY = 0; chunkY < CHUNK_HEIGHT; chunkY++) {
                    for (int chunkZ = 0; chunkZ < CHUNK_WIDTH; chunkZ++) {
                        Vector3 blockPosition = {float(chunkX), float(chunkY), float(chunkZ)};
                        Block block = chunk.GetBlock(blockPosition);
                        if (block.type != Air) {
                            Mesh mesh = GenMeshCube(BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
                            Model model = LoadModelFromMesh(mesh);

                            model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = blockDataManager.BlockTextureDictionary[block.type];             // Set map diffuse texture

                            Vector3 mapPosition = {0.0f, 0.0f, 0.0f};          // Set model position

                            DrawModel(model, mapPosition, 1.0f, WHITE);
                        }
                    }
                }
            }
        }
    }
}

#endif