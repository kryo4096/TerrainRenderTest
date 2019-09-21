#include "MeshBuilder.hpp"
#include <iostream>

int MeshBuilder::addVertex(Vertex v) {
    vertices.push_back(v);
    return vertices.size()-1;
}

void MeshBuilder::addIndex(int index) {
    indices.push_back(index);
}

void MeshBuilder::addIndices(std::vector<int>& indices) {
    for(int index : indices) {
        addIndex(index);
    }
}

Mesh MeshBuilder::build() {
    if(indices.size() % 3 != 0) {
        std::cerr << "Warning: Index array length (" << indices.size() << ") isn't divisible by 3." << std::endl;
    }

    Mesh mesh(vertices, indices);
    return mesh;
}

