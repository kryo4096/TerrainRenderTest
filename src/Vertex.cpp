#include "Vertex.hpp"

Vertex::Vertex(const glm::vec3 &position, const glm::vec3 &color, const glm::vec3 &normal, const glm::vec2 &uv)
        : position(position), color(color), normal(normal), uv(uv) {}
