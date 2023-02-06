#ifndef MESHDATA_HPP
#define MESHDATA_HPP

#include "vector"
#include "unordered_map"
#include "direction.hpp"
#include "block.hpp"
#include "rlgl.h"

class ChunkMesh {
public:
    std::vector<float> vertices;
    std::vector<unsigned short> indices;
    std::vector<float> texcoords;

    void GenerateBlockMesh(Direction direction, Vector3 location, BlockType blockType, BlockType neighborBlock);

    void AddBlockFace(Direction direction, Vector3 location, BlockType blockType);

    void RenderChunkMesh();
};

void ChunkMesh::GenerateBlockMesh(Direction direction, Vector3 location, BlockType blockType, BlockType neighborBlock) {
    if (blockType == Air) {
        return;
    }

    if (neighborBlock == Air) {
//        if (blockType == Water) {
//            // TODO: Handle water
//        }

        AddBlockFace(direction, location, blockType);
    }
}

void ChunkMesh::AddBlockFace(Direction direction, Vector3 location, BlockType blockType) {
    float *uvs = blockDataManager->BlockFaceToUVs[blockType][direction];
    for (int i = 0; i < 8; ++i) {
        texcoords.push_back(uvs[i]);
    }

    switch (direction) {
        case Forward:
            // Bottom left
            vertices.push_back(location.x + 0.5f);
            vertices.push_back(location.y + 0.5f);
            vertices.push_back(location.z - 0.5f);

            // Top left
            vertices.push_back(location.x + 0.5f);
            vertices.push_back(location.y + 0.5f);
            vertices.push_back(location.z + 0.5f);

            // Top Right
            vertices.push_back(location.x - 0.5f);
            vertices.push_back(location.y + 0.5f);
            vertices.push_back(location.z + 0.5f);

            // Bottom right
            vertices.push_back(location.x - 0.5f);
            vertices.push_back(location.y + 0.5f);
            vertices.push_back(location.z - 0.5f);
            break;
        case Backward:
            // Bottom left
            vertices.push_back(location.x - 0.5f);
            vertices.push_back(location.y - 0.5f);
            vertices.push_back(location.z - 0.5f);

            // Top left
            vertices.push_back(location.x - 0.5f);
            vertices.push_back(location.y - 0.5f);
            vertices.push_back(location.z + 0.5f);

            // Top right
            vertices.push_back(location.x + 0.5f);
            vertices.push_back(location.y - 0.5f);
            vertices.push_back(location.z + 0.5f);

            // Bottom right
            vertices.push_back(location.x + 0.5f);
            vertices.push_back(location.y - 0.5f);
            vertices.push_back(location.z - 0.5f);
            break;
        case Up:
            // Bottom left
            vertices.push_back(location.x - 0.5f);
            vertices.push_back(location.y - 0.5f);
            vertices.push_back(location.z + 0.5f);

            // Top left
            vertices.push_back(location.x - 0.5f);
            vertices.push_back(location.y + 0.5f);
            vertices.push_back(location.z + 0.5f);

            // Top right
            vertices.push_back(location.x + 0.5f);
            vertices.push_back(location.y + 0.5f);
            vertices.push_back(location.z + 0.5f);

            // Bottom right
            vertices.push_back(location.x + 0.5f);
            vertices.push_back(location.y - 0.5f);
            vertices.push_back(location.z + 0.5f);
            break;
        case Down:
            // Bottom left
            vertices.push_back(location.x + 0.5f);
            vertices.push_back(location.y - 0.5f);
            vertices.push_back(location.z - 0.5f);

            // Top left
            vertices.push_back(location.x + 0.5f);
            vertices.push_back(location.y + 0.5f);
            vertices.push_back(location.z - 0.5f);

            // Top right
            vertices.push_back(location.x - 0.5f);
            vertices.push_back(location.y + 0.5f);
            vertices.push_back(location.z - 0.5f);

            // Bottom right
            vertices.push_back(location.x - 0.5f);
            vertices.push_back(location.y - 0.5f);
            vertices.push_back(location.z - 0.5f);
            break;
        case Left:
            // Bottom left
            vertices.push_back(location.x - 0.5f);
            vertices.push_back(location.y + 0.5f);
            vertices.push_back(location.z - 0.5f);

            // Top left
            vertices.push_back(location.x - 0.5f);
            vertices.push_back(location.y + 0.5f);
            vertices.push_back(location.z + 0.5f);

            // Top right
            vertices.push_back(location.x - 0.5f);
            vertices.push_back(location.y - 0.5f);
            vertices.push_back(location.z + 0.5f);

            // Bottom right
            vertices.push_back(location.x - 0.5f);
            vertices.push_back(location.y - 0.5f);
            vertices.push_back(location.z - 0.5f);
            break;
        case Right:
            // Bottom left
            vertices.push_back(location.x + 0.5f);
            vertices.push_back(location.y - 0.5f);
            vertices.push_back(location.z - 0.5f);

            // Top left
            vertices.push_back(location.x + 0.5f);
            vertices.push_back(location.y - 0.5f);
            vertices.push_back(location.z + 0.5f);

            // Top right
            vertices.push_back(location.x + 0.5f);
            vertices.push_back(location.y + 0.5f);
            vertices.push_back(location.z + 0.5f);

            // Bottom right
            vertices.push_back(location.x + 0.5f);
            vertices.push_back(location.y + 0.5f);
            vertices.push_back(location.z - 0.5f);
            break;
    }

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);

    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(0);
}

void ChunkMesh::RenderChunkMesh() {
    Mesh m = { 0 };
    m.vertices = &vertices[0];
    m.vertexCount = vertices.size();

    m.indices = &indices[0];
    m.triangleCount = indices.size() / 3;

    m.texcoords = &texcoords[0];

    UploadMesh(&m, false);

    DrawMesh(m, blockDataManager->atlas, MatrixIdentity());
}

#endif
