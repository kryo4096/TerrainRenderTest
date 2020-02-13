#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <GL/glew.h>

#define GLM_SWIZZLE 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

class Transform {
private:
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;
    bool dirty;

    glm::mat4 matRepr;

public:
    Transform();

    void translate(glm::vec3 delta);
    void translateLocal(glm::vec3 delta);
    void translateLocalNormalizedInPlane(glm::vec3 delta, glm::vec3 normal);
    void rotate(glm::quat rotation);

    glm::vec3 getPosition();
    glm::quat getRotation();
    glm::vec3 getScale();

    void setPosition(glm::vec3 position);
    void setRotation(glm::quat rotation);
    void setScale(glm::vec3 scale);

    glm::mat4 matrix();
    glm::mat4 inverseMatrix();

    void debug();
};

#endif