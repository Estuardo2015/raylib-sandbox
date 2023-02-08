#ifndef CHUNK_HPP
#define CHUNK_HPP

#include "block.hpp"
#include "utils.hpp"
#include <functional>
#include "raylib.h"
#include "meshData.hpp"
#include "PerlinNoise.hpp"

const int CHUNK_WIDTH = 32; // 16 In blocks
const int CHUNK_HEIGHT = 50; // 100

class Chunk {
public:
    Block blocks[CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT];
    int blocksLength = CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT;
    Vector2 worldPosition;
    ChunkMesh chunkMesh;
    bool modified = true;

    Chunk();

    Chunk(Vector2);

    void GenerateTerrain(siv::PerlinNoise, float, int);

    void SetBlock(Vector3, Block);

    bool InRange(int);

    bool InRangeHeight(int);

    Block GetBlock(Vector3, std::vector<std::vector<Chunk>>*, Vector3, int);

    Vector3 IndexToVector3(unsigned int);

    int Vector3ToIndex(Vector3);

    void Update(std::vector<std::vector<Chunk>>*, int);

    void Render();
};

Chunk::Chunk() {
    chunkMesh.mesh = { 0 };
}

Chunk::Chunk(Vector2 wp) {
    worldPosition = wp;
    chunkMesh.mesh = { 0 };
}

void Chunk::GenerateTerrain(siv::PerlinNoise perlin, float noiseScale, int waterThreshold) {
    for (float x = 0; x < CHUNK_WIDTH; x++) {
        for (float z = 0; z < CHUNK_WIDTH; z++) {
            for (float y = 0; y < CHUNK_HEIGHT; y++) {
                double noiseValue = perlin.noise3D(((CHUNK_WIDTH * worldPosition.x) + x) * noiseScale, (0 + y) * noiseScale, ((CHUNK_WIDTH * worldPosition.y) + z) * noiseScale);
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

                SetBlock({x, y, z}, Block(blockType));
            }
        }
    }
}

void Chunk::SetBlock(Vector3 localPosition, Block block) {
    int index = Vector3ToIndex(localPosition);
    blocks[index] = block;
}

bool Chunk::InRange(int axisCoordinate) {
    if (axisCoordinate < 0 || axisCoordinate >= CHUNK_WIDTH)
        return false;

    return true;
}

bool Chunk::InRangeHeight(int ycoordinate) {
    if (ycoordinate < 0 || ycoordinate >= CHUNK_HEIGHT)
        return false;

    return true;
}

void Chunk::Update(std::vector<std::vector<Chunk>>* chunkMapReference, int worldWidth) {
    if (modified) {
        for (int i = 0; i < blocksLength; i++) {
            Vector3 position = IndexToVector3(i);
            Vector3 worldPos;

            worldPos.x = (CHUNK_WIDTH * worldPosition.x) + position.x;
            worldPos.z = (CHUNK_WIDTH * worldPosition.y) + position.z;
            worldPos.y = position.y;

            // Get neighbor blocks
            for (Direction direction: directions) {
                Vector3 directionVector = GetDirectionVector(direction);
                Vector3 neighbourBlockCoordinates = Vector3Add(position, directionVector);
                Block neighborBlock = GetBlock(neighbourBlockCoordinates, chunkMapReference, directionVector, worldWidth);

                chunkMesh.GenerateBlockMesh(direction, worldPos, blocks[i].type, neighborBlock.type);
            }
        }

        chunkMesh.RefreshMesh();
        modified = false;
    }
}

Block Chunk::GetBlock(Vector3 localPosition, std::vector<std::vector<Chunk>>* chunkMapReference, Vector3 directionVector, int worldWidth) {
    if (InRange(localPosition.x) && InRangeHeight(localPosition.y) && InRange(localPosition.z)) {
        int index = Vector3ToIndex(localPosition);
        return blocks[index];
    }

    int neighborChunkX = worldPosition.x + directionVector.x;
    int neighborChunkZ = worldPosition.y + directionVector.z;

    // Check if neighbor chunk is outside of world bounds
    if (neighborChunkX < 0 ||
        neighborChunkX >= worldWidth ||
        neighborChunkZ < 0 ||
        neighborChunkZ >= worldWidth) {
        return Air;
    }

    Chunk *chunk = &(*chunkMapReference)[neighborChunkX][neighborChunkZ];

    int index = 0;
    if (directionVector.x != 0 && directionVector.x > 0) {
        index = chunk->Vector3ToIndex({0, localPosition.y, localPosition.z});
    } else if (directionVector.x != 0 && directionVector.x < 0) {
        index = chunk->Vector3ToIndex({CHUNK_WIDTH-1, localPosition.y, localPosition.z});
    } else if (directionVector.z != 0 && directionVector.z > 0) {
        index = chunk->Vector3ToIndex({localPosition.x, localPosition.y, 0});
    } else if (directionVector.z != 0 && directionVector.z < 0) {
        index = chunk->Vector3ToIndex({localPosition.x, localPosition.y, CHUNK_WIDTH-1});
    }

    return chunk->blocks[index];
}

void Chunk::Render() {
    chunkMesh.RenderChunkMesh();
}

Vector3 Chunk::IndexToVector3(unsigned int idx) {
    float x = idx % CHUNK_WIDTH;
    float y = (idx / CHUNK_WIDTH) % CHUNK_HEIGHT;
    float z = idx / (CHUNK_WIDTH * CHUNK_HEIGHT);
    return Vector3{x, y, z};
}

int Chunk::Vector3ToIndex(Vector3 p) {
    return (p.z * CHUNK_WIDTH * CHUNK_HEIGHT) + (p.y * CHUNK_WIDTH) + p.x;
}

#endif