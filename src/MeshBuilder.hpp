#ifndef MESH_BUILDER_HPP
#define MESH_BUILDER_HPP

#include "Mesh.hpp"
#include <vector>


class MeshBuilder {
    std::vector<Vertex> vertices;
    std::vector<int> indices;
public:
    int addVertex(Vertex vertex);
    void addIndex(int index);
    void addIndices(std::vector<int>& indices);

    Mesh build();
};


#endif