#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>


struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 normal;
    glm::vec2 uv;

    Vertex(const glm::vec3 &position, const glm::vec3 &color, const glm::vec3 &normal, const glm::vec2 &uv);
};

#endif