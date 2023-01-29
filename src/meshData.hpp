#ifndef MESHDATA_HPP
#define MESHDATA_HPP

#include "vector"

class MeshData {
public:
    std::vector<float> vertices;
    std::vector<unsigned short> indices;
    std::vector<float> texcoords;
    std::vector<float> normals;

    void AddVertex(Vector3);
    void AddQuadTriangles();
};

void MeshData::AddVertex(Vector3 vertex) {
    vertices.push_back(vertex.x);
    vertices.push_back(vertex.y);
    vertices.push_back(vertex.z);
}

void MeshData::AddQuadTriangles() {
    // 0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3
    // 0        1        2        3
    // size = 12

    indices.push_back((vertices.size() / 3) - 4);
    indices.push_back((vertices.size() / 3) - 3);
    indices.push_back((vertices.size() / 3) - 2);

    indices.push_back((vertices.size() / 3) - 4);
    indices.push_back((vertices.size() / 3) - 2);
    indices.push_back((vertices.size() / 3) - 1);
}

#endif
