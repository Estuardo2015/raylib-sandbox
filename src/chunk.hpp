#ifndef CHUNK_HPP
#define CHUNK_HPP

#include "block.hpp"
#include "utils.hpp"
#include <functional>
#include "raylib.h"

const int CHUNK_WIDTH = 16; // In blocks
const int CHUNK_HEIGHT = 100;

class Chunk {
public:
    Block blocks[CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT];
    int blocksLength = CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT;
    Vector2 worldPosition;
    float noiseScale = 0.3;

    Chunk();

    void IterateThroughBlocks(std::function<void(Vector3)> func);

    void SetBlock(Vector3 localPosition, Block block);

    Block GetBlock(Vector3 localPosition);

    Vector3 IndexToVector3(unsigned int idx);

    int Vector3ToIndex(Vector3 p);
};

Chunk::Chunk() {

}

void Chunk::IterateThroughBlocks(std::function<void(Vector3)> func) {
    for (int i = 0; i < blocksLength; i++) {
        Vector3 blockPosition = IndexToVector3(i);
        func(blockPosition);
    }
}

void Chunk::SetBlock(Vector3 localPosition, Block block) {
    int index = Vector3ToIndex(localPosition);
    blocks[index] = block;
}

Block Chunk::GetBlock(Vector3 localPosition) {
    int index = Vector3ToIndex(localPosition);
    return blocks[index];
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
