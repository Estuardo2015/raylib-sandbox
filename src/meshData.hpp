#ifndef MESHDATA_HPP
#define MESHDATA_HPP

#include "vector"
#include "unordered_map"
#include "direction.hpp"
#include "block.hpp"
#include "rlgl.h"

class FaceMesh {
public:
    Texture texture;
    std::pair<float, float> texcoords[4];
    float vertices[4][3];
};

class MeshData {
public:
    std::vector<FaceMesh> faceMeshes;

    void GenerateMeshData(Direction direction, Vector3 location, BlockType blockType, BlockType neighborBlock);

    void AddFaceQuad(Direction direction, Vector3 location, BlockType blockType);

    void RenderFaceQuad(FaceMesh);
};

void MeshData::GenerateMeshData(Direction direction, Vector3 location, BlockType blockType, BlockType neighborBlock) {
    if (blockType == Air) {
        return;
    }

    if (neighborBlock == Air) {
//        if (blockType == Water) {
//            // TODO: Handle water
//        }

        AddFaceQuad(direction, location, blockType);
    }
}

void MeshData::AddFaceQuad(Direction direction, Vector3 location, BlockType blockType) {
    FaceMesh faceMesh;

    faceMesh.texture = blockDataManager->BlockTextureDictionary[blockType][direction];

    switch (direction) {
        case Forward:
            faceMesh.texcoords[0].first = 1.0f; faceMesh.texcoords[0].second = 1.0f;
            faceMesh.vertices[0][0] = location.x - 0.5f;
            faceMesh.vertices[0][1] = location.y - 0.5f;
            faceMesh.vertices[0][2] = location.z + 0.5f;

            faceMesh.texcoords[1].first = 0.0f; faceMesh.texcoords[1].second = 1.0f;
            faceMesh.vertices[1][0] = location.x + 0.5f;
            faceMesh.vertices[1][1] = location.y - 0.5f;
            faceMesh.vertices[1][2] = location.z + 0.5f;

            faceMesh.texcoords[2].first = 0.0f; faceMesh.texcoords[2].second = 0.0f;
            faceMesh.vertices[2][0] = location.x + 0.5f;
            faceMesh.vertices[2][1] = location.y + 0.5f;
            faceMesh.vertices[2][2] = location.z + 0.5f;

            faceMesh.texcoords[3].first = 1.0f; faceMesh.texcoords[3].second = 0.0f;
            faceMesh.vertices[3][0] = location.x - 0.5f;
            faceMesh.vertices[3][1] = location.y + 0.5f;
            faceMesh.vertices[3][2] = location.z + 0.5f;
            break;
        case Backward:
            faceMesh.texcoords[0].first = 0.0f; faceMesh.texcoords[0].second = 1.0f;
            faceMesh.vertices[0][0] = location.x - 0.5f;
            faceMesh.vertices[0][1] = location.y - 0.5f;
            faceMesh.vertices[0][2] = location.z - 0.5f;

            faceMesh.texcoords[1].first = 0.0f; faceMesh.texcoords[1].second = 0.0f;
            faceMesh.vertices[1][0] = location.x - 0.5f;
            faceMesh.vertices[1][1] = location.y + 0.5f;
            faceMesh.vertices[1][2] = location.z - 0.5f;

            faceMesh.texcoords[2].first = 1.0f; faceMesh.texcoords[2].second = 0.0f;
            faceMesh.vertices[2][0] = location.x + 0.5f;
            faceMesh.vertices[2][1] = location.y + 0.5f;
            faceMesh.vertices[2][2] = location.z - 0.5f;

            faceMesh.texcoords[3].first = 1.0f; faceMesh.texcoords[3].second = 1.0f;
            faceMesh.vertices[3][0] = location.x + 0.5f;
            faceMesh.vertices[3][1] = location.y - 0.5f;
            faceMesh.vertices[3][2] = location.z - 0.5f;
            break;
        case Up:
            faceMesh.texcoords[0].first = 0.0f; faceMesh.texcoords[0].second = 1.0f;
            faceMesh.vertices[0][0] = location.x - 0.5f;
            faceMesh.vertices[0][1] = location.y + 0.5f;
            faceMesh.vertices[0][2] = location.z - 0.5f;

            faceMesh.texcoords[1].first = 0.0f; faceMesh.texcoords[1].second = 0.0f;
            faceMesh.vertices[1][0] = location.x - 0.5f;
            faceMesh.vertices[1][1] = location.y + 0.5f;
            faceMesh.vertices[1][2] = location.z + 0.5f;

            faceMesh.texcoords[2].first = 1.0f; faceMesh.texcoords[2].second = 0.0f;
            faceMesh.vertices[2][0] = location.x + 0.5f;
            faceMesh.vertices[2][1] = location.y + 0.5f;
            faceMesh.vertices[2][2] = location.z + 0.5f;

            faceMesh.texcoords[3].first = 1.0f; faceMesh.texcoords[3].second = 1.0f;
            faceMesh.vertices[3][0] = location.x + 0.5f;
            faceMesh.vertices[3][1] = location.y + 0.5f;
            faceMesh.vertices[3][2] = location.z - 0.5f;
            break;
        case Down:
            faceMesh.texcoords[0].first = 1.0f; faceMesh.texcoords[0].second = 1.0f;
            faceMesh.vertices[0][0] = location.x - 0.5f;
            faceMesh.vertices[0][1] = location.y - 0.5f;
            faceMesh.vertices[0][2] = location.z - 0.5f;

            faceMesh.texcoords[1].first = 0.0f; faceMesh.texcoords[1].second = 1.0f;
            faceMesh.vertices[1][0] = location.x + 0.5f;
            faceMesh.vertices[1][1] = location.y - 0.5f;
            faceMesh.vertices[1][2] = location.z - 0.5f;

            faceMesh.texcoords[2].first = 0.0f; faceMesh.texcoords[2].second = 0.0f;
            faceMesh.vertices[2][0] = location.x + 0.5f;
            faceMesh.vertices[2][1] = location.y - 0.5f;
            faceMesh.vertices[2][2] = location.z + 0.5f;

            faceMesh.texcoords[3].first = 1.0f; faceMesh.texcoords[3].second = 0.0f;
            faceMesh.vertices[3][0] = location.x - 0.5f;
            faceMesh.vertices[3][1] = location.y - 0.5f;
            faceMesh.vertices[3][2] = location.z + 0.5f;
            break;
        case Left:
            faceMesh.texcoords[0].first = 1.0f; faceMesh.texcoords[0].second = 1.0f;
            faceMesh.vertices[0][0] = location.x - 0.5f;
            faceMesh.vertices[0][1] = location.y - 0.5f;
            faceMesh.vertices[0][2] = location.z - 0.5f;

            faceMesh.texcoords[1].first = 0.0f; faceMesh.texcoords[1].second = 1.0f;
            faceMesh.vertices[1][0] = location.x - 0.5f;
            faceMesh.vertices[1][1] = location.y - 0.5f;
            faceMesh.vertices[1][2] = location.z + 0.5f;

            faceMesh.texcoords[2].first = 0.0f; faceMesh.texcoords[2].second = 0.0f;
            faceMesh.vertices[2][0] = location.x - 0.5f;
            faceMesh.vertices[2][1] = location.y + 0.5f;
            faceMesh.vertices[2][2] = location.z + 0.5f;

            faceMesh.texcoords[3].first = 1.0f; faceMesh.texcoords[3].second = 0.0f;
            faceMesh.vertices[3][0] = location.x - 0.5f;
            faceMesh.vertices[3][1] = location.y + 0.5f;
            faceMesh.vertices[3][2] = location.z - 0.5f;
            break;
        case Right:
            faceMesh.texcoords[0].first = 0.0f; faceMesh.texcoords[0].second = 1.0f;
            faceMesh.vertices[0][0] = location.x + 0.5f;
            faceMesh.vertices[0][1] = location.y - 0.5f;
            faceMesh.vertices[0][2] = location.z - 0.5f;

            faceMesh.texcoords[1].first = 0.0f; faceMesh.texcoords[1].second = 0.0f;
            faceMesh.vertices[1][0] = location.x + 0.5f;
            faceMesh.vertices[1][1] = location.y + 0.5f;
            faceMesh.vertices[1][2] = location.z - 0.5f;

            faceMesh.texcoords[2].first = 1.0f; faceMesh.texcoords[2].second = 0.0f;
            faceMesh.vertices[2][0] = location.x + 0.5f;
            faceMesh.vertices[2][1] = location.y + 0.5f;
            faceMesh.vertices[2][2] = location.z + 0.5f;

            faceMesh.texcoords[3].first = 1.0f; faceMesh.texcoords[3].second = 1.0f;
            faceMesh.vertices[3][0] = location.x + 0.5f;
            faceMesh.vertices[3][1] = location.y - 0.5f;
            faceMesh.vertices[3][2] = location.z + 0.5f;
            break;
    }

    faceMeshes.push_back(faceMesh);
}

void MeshData::RenderFaceQuad(FaceMesh faceMesh) {
    rlCheckRenderBatchLimit(6);

    rlSetTexture(faceMesh.texture.id);

    rlBegin(RL_QUADS);

    for (int i = 0; i < 4; ++i) {
        rlTexCoord2f(faceMesh.texcoords[i].first, faceMesh.texcoords[i].second);
        rlVertex3f(faceMesh.vertices[i][0], faceMesh.vertices[i][1], faceMesh.vertices[i][2]);
    }

    rlEnd();
    rlSetTexture(0);
}

#endif
