#ifndef MESHDATA_HPP
#define MESHDATA_HPP

#include "vector"
#include "unordered_map"
#include "direction.hpp"
#include "block.hpp"
#include "rlgl.h"

class ChunkMesh {
public:
    Mesh mesh;
    std::vector<float> vertices;
    std::vector<unsigned short> indices;
    std::vector<float> texcoords;

    void GenerateBlockMesh(Direction direction, Vector3 location, BlockType blockType, BlockType neighborBlock);

    void AddBlockFace(Direction direction, Vector3 location, BlockType blockType);

    void RefreshMesh();

    void RenderChunkMesh();
};

void ChunkMesh::GenerateBlockMesh(Direction direction, Vector3 location, BlockType blockType, BlockType neighborBlock) {
    if ((blockType == Air) || (location.y == 0 && direction == Down)) {
        return;
    }

    if (neighborBlock == Air) {
        AddBlockFace(direction, location, blockType);
    }
}

void ChunkMesh::AddBlockFace(Direction direction, Vector3 location, BlockType blockType) {
    for (int i = 0; i < 8; ++i) {
        texcoords.push_back(blockDataManager->BlockFaceToUVs[blockType][direction][i]);
    }

    switch (direction) {
        case Forward:
            vertices.push_back(location.x - 0.5f);
            vertices.push_back(location.y - 0.5f);
            vertices.push_back(location.z + 0.5f);

            vertices.push_back(location.x + 0.5f);
            vertices.push_back(location.y - 0.5f);
            vertices.push_back(location.z + 0.5f);

            vertices.push_back(location.x + 0.5f);
            vertices.push_back(location.y + 0.5f);
            vertices.push_back(location.z + 0.5f);

            vertices.push_back(location.x - 0.5f);
            vertices.push_back(location.y + 0.5f);
            vertices.push_back(location.z + 0.5f);

            break;
        case Backward:
            vertices.push_back(location.x + 0.5f);
            vertices.push_back(location.y - 0.5f);
            vertices.push_back(location.z - 0.5f);

            vertices.push_back(location.x - 0.5f);
            vertices.push_back(location.y - 0.5f);
            vertices.push_back(location.z - 0.5f);

            vertices.push_back(location.x - 0.5f);
            vertices.push_back(location.y + 0.5f);
            vertices.push_back(location.z - 0.5f);

            vertices.push_back(location.x + 0.5f);
            vertices.push_back(location.y + 0.5f);
            vertices.push_back(location.z - 0.5f);

            break;
        case Up:
            vertices.push_back(location.x - 0.5f);
            vertices.push_back(location.y + 0.5f);
            vertices.push_back(location.z + 0.5f);

            vertices.push_back(location.x + 0.5f);
            vertices.push_back(location.y + 0.5f);
            vertices.push_back(location.z + 0.5f);

            vertices.push_back(location.x + 0.5f);
            vertices.push_back(location.y + 0.5f);
            vertices.push_back(location.z - 0.5f);

            vertices.push_back(location.x - 0.5f);
            vertices.push_back(location.y + 0.5f);
            vertices.push_back(location.z - 0.5f);

            break;
        case Down:
            vertices.push_back(location.x - 0.5f);
            vertices.push_back(location.y - 0.5f);
            vertices.push_back(location.z - 0.5f);

            vertices.push_back(location.x + 0.5f);
            vertices.push_back(location.y - 0.5f);
            vertices.push_back(location.z - 0.5f);

            vertices.push_back(location.x + 0.5f);
            vertices.push_back(location.y - 0.5f);
            vertices.push_back(location.z + 0.5f);

            vertices.push_back(location.x - 0.5f);
            vertices.push_back(location.y - 0.5f);
            vertices.push_back(location.z + 0.5f);

            break;
        case Left:
            vertices.push_back(location.x - 0.5f);
            vertices.push_back(location.y - 0.5f);
            vertices.push_back(location.z - 0.5f);

            vertices.push_back(location.x - 0.5f);
            vertices.push_back(location.y - 0.5f);
            vertices.push_back(location.z + 0.5f);

            vertices.push_back(location.x - 0.5f);
            vertices.push_back(location.y + 0.5f);
            vertices.push_back(location.z + 0.5f);

            vertices.push_back(location.x - 0.5f);
            vertices.push_back(location.y + 0.5f);
            vertices.push_back(location.z - 0.5f);

            break;
        case Right:
            vertices.push_back(location.x + 0.5f);
            vertices.push_back(location.y - 0.5f);
            vertices.push_back(location.z + 0.5f);

            vertices.push_back(location.x + 0.5f);
            vertices.push_back(location.y - 0.5f);
            vertices.push_back(location.z - 0.5f);

            vertices.push_back(location.x + 0.5f);
            vertices.push_back(location.y + 0.5f);
            vertices.push_back(location.z - 0.5f);

            vertices.push_back(location.x + 0.5f);
            vertices.push_back(location.y + 0.5f);
            vertices.push_back(location.z + 0.5f);

            break;
    }

    int numVertices = vertices.size();
    indices.push_back((numVertices / 3) - 4);
    indices.push_back((numVertices / 3) - 3);
    indices.push_back((numVertices / 3) - 2);

    indices.push_back((numVertices / 3) - 2);
    indices.push_back((numVertices / 3) - 1);
    indices.push_back((numVertices / 3) - 4);
}

void ChunkMesh::RefreshMesh() {
    mesh.vertices = &vertices[0];
    mesh.vertexCount = vertices.size() / 3;

    mesh.indices = &indices[0];
    mesh.triangleCount = indices.size() / 3;

    mesh.texcoords = &texcoords[0];

    UploadMesh(&mesh, false);
}

void ChunkMesh::RenderChunkMesh() {
    DrawMesh(mesh, blockDataManager->atlas, MatrixIdentity());
}

#endif
