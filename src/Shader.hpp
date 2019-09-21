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

    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* geometryPath);
        
    void use();

    void setBool(const std::string &name, bool value) const;

    void setInt(const std::string &name, int value) const;

    void setMat4(const std::string &name, glm::mat4 matrix);
    
    void setFloat(const std::string &name, float value) const;
};

#endif