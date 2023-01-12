#ifndef WORLD_H
#define WORLD_H

#include "block.h"

const int WORLD_SIZE = 1; // In chunks
const int CHUNK_SIZE = 16; // 256 blocks

class Chunk {
    public:
        Block blocks[CHUNK_SIZE];
};

class World {
    public:
        Chunk chunks[WORLD_SIZE];
};

World NewTestWorld() {
    World w;
    for (int i = 0; i < WORLD_SIZE; i++) {
        w.chunks[i] = Chunk{};
        for (int j = 0; j < CHUNK_SIZE; j++) {
            unsigned short int mat = 1;
            if (j % 2 == 0) {
                mat = 2;
            }

            w.chunks[i].blocks[j] = Block{mat};
        }
    }

    return w;
}

int GetIndex(Vector3 p, unsigned int xMax, unsigned int yMax) {
    return (p.z * xMax * yMax) + (p.y * xMax) + p.x;
}

Vector3 IndexTo3D(unsigned int idx, unsigned int xMax, unsigned int yMax) {
    float z = idx / (xMax * yMax);
    idx -= (z * xMax * yMax);

    float y = idx / xMax;

    float x = idx % xMax;

    return Vector3{x, y, z};
}

#endif
