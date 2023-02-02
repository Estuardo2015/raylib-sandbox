#ifndef MESHDATA_HPP
#define MESHDATA_HPP

#include "vector"
#include "../include/raymath.h"
#include "direction.hpp"
#include "block.hpp"

class MeshData {
public:
    Model model = { 0 };
    std::vector<Mesh> meshes;
    std::vector<Material> materials;
    std::vector<int> meshMaterials;

    MeshData();

    void AddFaceQuad(Direction direction, Vector3 location, BlockType blockType);

    void GetMeshData(Vector3, BlockType);
};

MeshData::MeshData() {
    model.transform = MatrixIdentity();
}

void MeshData::GetMeshData(Vector3 location, BlockType blockType) {
    if (blockType == Air) {
        return;
    }

    for (Direction direction: directions) {
        //Vector3 neighbourBlockCoordinates = Vector3Add(location, GetDirectionVector(direction));
        //Block neighborBlock = chunk.GetBlock(neighbourBlockCoordinates);

        if (blockType == Water) {
            // TODO: Handle water
        } else {
            AddFaceQuad(direction, location, blockType);
        }
    }
}

void MeshData::AddFaceQuad(Direction direction, Vector3 location, BlockType blockType) {
    std::vector<float> vertices;

    switch (direction) {
        case Backward:
            vertices = {location.x - 0.5f, location.y - 0.5f, location.z - 0.5f,
                        location.x - 0.5f, location.y + 0.5f, location.z - 0.5f,
                        location.x + 0.5f, location.y + 0.5f, location.z - 0.5f,
                        location.x + 0.5f, location.y - 0.5f, location.z - 0.5f};
            break;
        case Forward:
            vertices = {location.x + 0.5f, location.y - 0.5f, location.z + 0.5f,
                        location.x + 0.5f, location.y + 0.5f, location.z + 0.5f,
                        location.x - 0.5f, location.y + 0.5f, location.z + 0.5f,
                        location.x - 0.5f, location.y - 0.5f, location.z + 0.5f};
            break;
        case Left:
            vertices = {location.x - 0.5f, location.y - 0.5f, location.z + 0.5f,
                        location.x - 0.5f, location.y + 0.5f, location.z + 0.5f,
                        location.x - 0.5f, location.y + 0.5f, location.z - 0.5f,
                        location.x - 0.5f, location.y - 0.5f, location.z - 0.5f};
            break;
        case Right:
            vertices = {location.x + 0.5f, location.y - 0.5f, location.z - 0.5f,
                        location.x + 0.5f, location.y + 0.5f, location.z - 0.5f,
                        location.x + 0.5f, location.y + 0.5f, location.z + 0.5f,
                        location.x + 0.5f, location.y - 0.5f, location.z + 0.5f};
            break;
        case Down:
            vertices = {location.x - 0.5f, location.y - 0.5f, location.z - 0.5f,
                        location.x + 0.5f, location.y - 0.5f, location.z - 0.5f,
                        location.x + 0.5f, location.y - 0.5f, location.z + 0.5f,
                        location.x - 0.5f, location.y - 0.5f, location.z + 0.5f};
            break;
        case Up:
            vertices = {location.x - 0.5f, location.y + 0.5f, location.z + 0.5f,
                        location.x + 0.5f, location.y + 0.5f, location.z + 0.5f,
                        location.x + 0.5f, location.y + 0.5f, location.z - 0.5f,
                        location.x - 0.5f, location.y + 0.5f, location.z - 0.5f};
            break;
    }

    unsigned short indices[6] = {
            0, 1, 2,
            2, 3, 0
    };

    float texcoords[8] = {
            0.0, 1.0,
            0.0, 0.0,
            1.0, 0.0,
            1.0, 1.0,
    };

    // Create new mesh
    Mesh mesh { 0 };
    mesh.vertexCount = 4;
    mesh.vertices = &vertices[0];

    mesh.indices = indices;
    mesh.triangleCount = 2;

    mesh.texcoords = texcoords;

    UploadMesh(&mesh, false);

    // Load texture
    Material material = LoadMaterialDefault();
    Texture texture = blockDataManager->BlockTextureDictionary[blockType][direction];
    SetMaterialTexture(&material, MATERIAL_MAP_DIFFUSE, texture);

    // Add mesh to the model
    meshes.push_back(mesh);
    model.meshCount = meshes.size();
    model.meshes = &meshes[0];

    // Add material to the model
    materials.push_back(material);
    model.materialCount = materials.size();
    model.materials = &materials[0];

    // Update meshMaterial array
    meshMaterials.push_back(meshMaterials.size());
    model.meshMaterial = &meshMaterials[0];
}

#endif
