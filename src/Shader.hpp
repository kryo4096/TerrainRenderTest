#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>

class Shader {
    GLuint program;
public:
    Shader(const std::string &vertexSource, const std::string &fragmentSource, const std::string &geometrySource);
    Shader(const std::string &vertexSource, const std::string &fragmentSource);
        
    void use();

    void setBool(const std::string &name, bool value) const;

    void setInt(const std::string &name, int value) const;

    void setMat4(const std::string &name, glm::mat4 matrix);

    void setVec3(const std::string &name, glm::vec3 vector);
    
    void setFloat(const std::string &name, float value) const;
};

#endif