#include "Shader.hpp"
#include <vector>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;



GLuint createProgram(vector<GLuint> shaders) {
    auto program = glCreateProgram();

    for(auto shader : shaders) {
        glAttachShader(program, shader);
    }

    int success;
    char infoLog[512];

    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if(!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "Shader Program compilation failed:" << std::endl << infoLog << std::endl;
    }

    for(auto shader : shaders) {
        glDeleteShader(shader);
    }

    return program;
}

GLuint compileShader(const string& shaderSource, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);

    auto shaderCstr = shaderSource.c_str();

    glShaderSource(shader, 1, &shaderCstr, NULL);

    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    auto typeText = shaderType == GL_VERTEX_SHADER ? "Vertex shader" :
        shaderType == GL_FRAGMENT_SHADER ? "Fragment shader" :
        shaderType == GL_GEOMETRY_SHADER ? "Geometry shader" : "invalid shader";

    if(!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << typeText << " compilation failed:" << std::endl << infoLog << std::endl;
    } else {
        std::cout << typeText << " compiled successfully." << std::endl;
    }

    return shader;
}


Shader::Shader(const string& vertexSource, const string& fragmentSource, const string& geometrySource) {
    auto vertexShader = compileShader(vertexSource, GL_VERTEX_SHADER);
    auto fragmentShader = compileShader(fragmentSource, GL_FRAGMENT_SHADER);
    auto geometryShader = compileShader(geometrySource, GL_GEOMETRY_SHADER);
    program = createProgram({vertexShader, geometryShader, fragmentShader});
}

Shader::Shader(const string& vertexSource, const string& fragmentSource) {
    auto vertexShader = compileShader(vertexSource, GL_VERTEX_SHADER);
    auto fragmentShader = compileShader(fragmentSource, GL_FRAGMENT_SHADER);
    program = createProgram({vertexShader, fragmentShader});
}
    
void Shader::use() {
    glUseProgram(program);
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(program, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}

void Shader::setMat4(const std::string &name, glm::mat4 matrix){
    glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}

void Shader::setVec3(const std::string &name, glm::vec3 vector) {
    glUniform3fv(glGetUniformLocation(program, name.c_str()), 1, glm::value_ptr(vector));
}

