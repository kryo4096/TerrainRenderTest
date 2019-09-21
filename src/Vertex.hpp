#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>


struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 normal;
    
    Vertex(glm::vec3 position, glm::vec3 color, glm::vec3 normal);
};

#endif