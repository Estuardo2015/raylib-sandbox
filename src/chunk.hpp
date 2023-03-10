#ifndef CHUNK_HPP
#define CHUNK_HPP

#include "block.hpp"
#include "utils.hpp"
#include <functional>
#include "raylib.h"
#include "meshData.hpp"

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

    void SetBlock(Vector3 localPosition, Block block);

    bool InRange(int);

    bool InRangeHeight(int);

    Block GetBlock(Vector3 localPosition);

    Vector3 IndexToVector3(unsigned int idx);

    int Vector3ToIndex(Vector3 p);

    void Update(int, int);

    void Render();
};

Chunk::Chunk() {
    chunkMesh.mesh = { 0 };
}

Chunk::Chunk(Vector2 wp) {
    worldPosition = wp;
    chunkMesh.mesh = { 0 };
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

Block Chunk::GetBlock(Vector3 localPosition) {
    if (InRange(localPosition.x) && InRangeHeight(localPosition.y) && InRange(localPosition.z)) {
        int index = Vector3ToIndex(localPosition);
        return blocks[index];
    }

    return Block(Air);

    //return chunkData.worldReference.GetBlockFromChunkCoordinates(chunkData, chunkData.worldPosition.x + x, chunkData.worldPosition.y + y, chunkData.worldPosition.z
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

void Chunk::Update(int worldX, int worldZ) {
    if (modified) {
        for (int i = 0; i < blocksLength; i++) {
            Vector3 position = IndexToVector3(i);
            Vector3 worldPos;

            worldPos.x = (CHUNK_WIDTH * worldX) + position.x;
            worldPos.z = (CHUNK_WIDTH * worldZ) + position.z;
            worldPos.y = position.y;

            // Get neighbor blocks
            std::unordered_map<Direction, BlockType> neighbors;
            for (Direction direction: directions) {
                Vector3 neighbourBlockCoordinates = Vector3Add(position, GetDirectionVector(direction));
                Block neighborBlock = GetBlock(neighbourBlockCoordinates);

                chunkMesh.GenerateBlockMesh(direction, worldPos, blocks[i].type, neighborBlock.type);
            }
        }

        chunkMesh.RefreshMesh();

        modified = false;
    }
}

void Chunk::Render() {
    chunkMesh.RenderChunkMesh();
}

#endif