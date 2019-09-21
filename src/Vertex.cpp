#include "Vertex.hpp"

Vertex::Vertex(glm::vec3 _position, glm::vec3 _color, glm::vec3 _normal) {
    this->position = _position;
    this->color = _color;
    this->normal = _normal;
}
