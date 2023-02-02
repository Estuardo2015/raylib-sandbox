#ifndef CHUNK_HPP
#define CHUNK_HPP

#include "block.hpp"
#include "utils.hpp"
#include <functional>
#include "raylib.h"
#include "meshData.hpp"

const int CHUNK_WIDTH = 16; // In blocks
const int CHUNK_HEIGHT = 100;

class Chunk {
public:
    Block blocks[CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT];
    int blocksLength = CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT;
    Vector2 worldPosition;

    Chunk();

    Chunk(Vector2);

    void SetBlock(Vector3 localPosition, Block block);

    bool InRange(int);

    bool InRangeHeight(int);

    Block GetBlock(Vector3 localPosition);

    Vector3 IndexToVector3(unsigned int idx);

    int Vector3ToIndex(Vector3 p);

    MeshData GetChunkMeshData();

    void RenderChunk();
};

Chunk::Chunk() {

}

Chunk::Chunk(Vector2 wp) {
    worldPosition = wp;
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

MeshData Chunk::GetChunkMeshData() {
            MeshData meshData = MeshData{};

    for (int i = 0; i < blocksLength; i++) {
        Vector3 position = IndexToVector3(i);
        meshData.GetMeshData(position, blocks[i].type);
    }

    return meshData;
}

void Chunk::RenderChunk() {
    MeshData meshData = GetChunkMeshData();

    Mesh mesh = Mesh{ 0 };
    mesh.vertices = &meshData.vertices[0];
    mesh.vertexCount = meshData.vertices.size();

    mesh.indices = &meshData.indices[0];
    mesh.triangleCount = mesh.vertexCount/9;

    Model model = LoadModelFromMesh(mesh);

    DrawModel(model, {worldPosition.x, worldPosition.y, 0}, 1, WHITE);
}

#endif
