#ifndef MESHDATA_HPP
#define MESHDATA_HPP

#include "vector"
#include "unordered_map"
#include "direction.hpp"
#include "block.hpp"
#include "rlgl.h"

class MeshData {
public:
    Model model = { 0 };
    std::vector<Mesh> meshes;
    std::vector<Material> materials;
    std::vector<int> meshMaterials;

    MeshData();

    void AddFaceQuad(Direction direction, Vector3 location, BlockType blockType);

    void GetMeshData(Direction, Vector3, BlockType, BlockType);
};

MeshData::MeshData() {
    model.transform = MatrixIdentity();
}

void MeshData::GetMeshData(Direction direction, Vector3 location, BlockType blockType, BlockType neighborBlock) {
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
    Texture texture = blockDataManager->BlockTextureDictionary[blockType][direction];

    rlCheckRenderBatchLimit(6);

    rlSetTexture(texture.id);

    rlBegin(RL_QUADS);

    switch (direction) {
        case Forward:
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(location.x - 0.5f, location.y - 0.5f, location.z + 0.5f);
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(location.x + 0.5f, location.y - 0.5f, location.z + 0.5f);
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(location.x + 0.5f, location.y + 0.5f, location.z + 0.5f);
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(location.x - 0.5f, location.y + 0.5f, location.z + 0.5f);
            break;
        case Backward:
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(location.x - 0.5f, location.y - 0.5f, location.z - 0.5f);
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(location.x - 0.5f, location.y + 0.5f, location.z - 0.5f);
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(location.x + 0.5f, location.y + 0.5f, location.z - 0.5f);
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(location.x + 0.5f, location.y - 0.5f, location.z - 0.5f);
            break;
        case Up:
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(location.x - 0.5f, location.y + 0.5f, location.z - 0.5f);
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(location.x - 0.5f, location.y + 0.5f, location.z + 0.5f);
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(location.x + 0.5f, location.y + 0.5f, location.z + 0.5f);
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(location.x + 0.5f, location.y + 0.5f, location.z - 0.5f);
            break;
        case Down:
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(location.x - 0.5f, location.y - 0.5f, location.z - 0.5f);
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(location.x + 0.5f, location.y - 0.5f, location.z - 0.5f);
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(location.x + 0.5f, location.y - 0.5f, location.z + 0.5f);
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(location.x - 0.5f, location.y - 0.5f, location.z + 0.5f);
            break;
        case Left:
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(location.x - 0.5f, location.y - 0.5f, location.z - 0.5f);
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(location.x - 0.5f, location.y - 0.5f, location.z + 0.5f);
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(location.x - 0.5f, location.y + 0.5f, location.z + 0.5f);
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(location.x - 0.5f, location.y + 0.5f, location.z - 0.5f);
            break;
        case Right:
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(location.x + 0.5f, location.y - 0.5f, location.z - 0.5f);
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(location.x + 0.5f, location.y + 0.5f, location.z - 0.5f);
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(location.x + 0.5f, location.y + 0.5f, location.z + 0.5f);
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(location.x + 0.5f, location.y - 0.5f, location.z + 0.5f);
            break;

    }
    rlEnd();
    rlSetTexture(0);
}

#endif
