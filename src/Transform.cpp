#include "Transform.hpp"

#include <glm/gtx/string_cast.hpp>
#include <iostream>


using namespace glm;

mat4 calculateMatrix(vec3 position, quat rotation, vec3 scale) {
    mat4 id = identity<mat4>();

    return glm::translate(id, position) * glm::toMat4(rotation) * glm::scale(id, scale);
}

Transform::Transform() {
    this->position = vec3(0,0,0);
    this->rotation = identity<quat>();
    this->scale = vec3(1,1,1);

    this->dirty = true;
}

mat4 Transform::matrix() {
    if(dirty) {
        matRepr = calculateMatrix(position, rotation, scale);
        dirty = false;
    }
    return matRepr;
}

mat4 Transform::inverseMatrix() {
    return inverse(matrix());
}

void Transform::translate(glm::vec3 delta) {
    dirty = true;

    position += delta;
}

void Transform::translateLocal(glm::vec3 delta) {
    dirty = true;

    position += (matrix() * vec4(delta, 0)).xyz();
}

void Transform::rotate(glm::quat _rotation) {
    dirty = true;

    rotation = _rotation * rotation;
}

glm::vec3 Transform::getPosition() {
    return position;
}

glm::quat Transform::getRotation() {
    return rotation;
}

glm::vec3 Transform::getScale() {
    return scale;
}

void Transform::setPosition(glm::vec3 _position) {
    dirty = true;

    position = _position;
}

void Transform::setRotation(glm::quat _rotation) {
    dirty = true;

    rotation = _rotation;
}

void Transform::setScale(glm::vec3 _scale) {
    dirty = true;

    scale = _scale;
}

void Transform::debug() {
    std::cout << 
        "Position:" << glm::to_string(position) << std::endl <<
        "Rotation:" << glm::to_string(rotation) << std::endl <<
        "Scale:" << glm::to_string(scale) << std::endl;
}