#ifndef MESHDATA_HPP
#define MESHDATA_HPP

#include "vector"
#include "../include/raymath.h"
#include "direction.hpp"
#include "block.hpp"

class MeshData {
public:
    std::vector<float> vertices;
    std::vector<unsigned short> indices;
    std::vector<float> texcoords;
    std::vector<float> normals;
    std::vector<Mesh> meshes;

    void AddVertex(Vector3);

    void AddQuadTriangles();

    void GetFaceVertices(Direction, Vector3, BlockType);

    void GetFaceMesh(Direction direction, Vector3 location, BlockType blockType);

    void GetMeshData(Vector3, BlockType);
};

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
            GetFaceMesh(direction, location, blockType);
        }
    }

    return;
}

void MeshData::GetFaceMesh(Direction direction, Vector3 location, BlockType blockType) {
    GetFaceVertices(direction, location, blockType);
    AddQuadTriangles();
    //meshData.uv.AddRange(FaceUVs(direction, blockType));
    Model model;
}

void MeshData::GetFaceVertices(Direction direction, Vector3 location, BlockType blockType) {
    switch (direction) {
        case Backward:
            AddVertex(Vector3{location.x - 0.5f, location.y - 0.5f, location.z - 0.5f});
            AddVertex(Vector3{location.x - 0.5f, location.y + 0.5f, location.z - 0.5f});
            AddVertex(Vector3{location.x + 0.5f, location.y + 0.5f, location.z - 0.5f});
            AddVertex(Vector3{location.x + 0.5f, location.y - 0.5f, location.z - 0.5f});
            break;
        case Forward:
            AddVertex(Vector3{location.x + 0.5f, location.y - 0.5f, location.z + 0.5f});
            AddVertex(Vector3{location.x + 0.5f, location.y + 0.5f, location.z + 0.5f});
            AddVertex(Vector3{location.x - 0.5f, location.y + 0.5f, location.z + 0.5f});
            AddVertex(Vector3{location.x - 0.5f, location.y - 0.5f, location.z + 0.5f});
            break;
        case Left:
            AddVertex(Vector3{location.x - 0.5f, location.y - 0.5f, location.z + 0.5f});
            AddVertex(Vector3{location.x - 0.5f, location.y + 0.5f, location.z + 0.5f});
            AddVertex(Vector3{location.x - 0.5f, location.y + 0.5f, location.z - 0.5f});
            AddVertex(Vector3{location.x - 0.5f, location.y - 0.5f, location.z - 0.5f});
            break;
        case Right:
            AddVertex(Vector3{location.x + 0.5f, location.y - 0.5f, location.z - 0.5f});
            AddVertex(Vector3{location.x + 0.5f, location.y + 0.5f, location.z - 0.5f});
            AddVertex(Vector3{location.x + 0.5f, location.y + 0.5f, location.z + 0.5f});
            AddVertex(Vector3{location.x + 0.5f, location.y - 0.5f, location.z + 0.5f});
            break;
        case Down:
            AddVertex(Vector3{location.x - 0.5f, location.y - 0.5f, location.z - 0.5f});
            AddVertex(Vector3{location.x + 0.5f, location.y - 0.5f, location.z - 0.5f});
            AddVertex(Vector3{location.x + 0.5f, location.y - 0.5f, location.z + 0.5f});
            AddVertex(Vector3{location.x - 0.5f, location.y - 0.5f, location.z + 0.5f});
            break;
        case Up:
            AddVertex(Vector3{location.x - 0.5f, location.y + 0.5f, location.z + 0.5f});
            AddVertex(Vector3{location.x + 0.5f, location.y + 0.5f, location.z + 0.5f});
            AddVertex(Vector3{location.x + 0.5f, location.y + 0.5f, location.z - 0.5f});
            AddVertex(Vector3{location.x - 0.5f, location.y + 0.5f, location.z - 0.5f});
            break;
    }
}

void MeshData::AddVertex(Vector3 vertex) {
    vertices.push_back(vertex.x);
    vertices.push_back(vertex.y);
    vertices.push_back(vertex.z);
}

void MeshData::AddQuadTriangles() {
    indices.push_back((vertices.size() / 3) - 4);
    indices.push_back((vertices.size() / 3) - 3);
    indices.push_back((vertices.size() / 3) - 2);

    indices.push_back((vertices.size() / 3) - 4);
    indices.push_back((vertices.size() / 3) - 2);
    indices.push_back((vertices.size() / 3) - 1);
}

#endif
