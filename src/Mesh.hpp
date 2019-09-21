#ifndef MESH_HPP
#define MESH_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "Vertex.hpp"

class Mesh {
private: 
    GLuint vbo;
    GLuint ebo;
    GLuint vao;
    int size;
public:
    Mesh(std::vector<Vertex>& vertices, std::vector<int>& indices);

    void draw() const;

    ~Mesh();
};

#endif

