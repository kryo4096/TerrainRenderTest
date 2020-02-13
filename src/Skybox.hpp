//
// Created by jonas on 11/11/19.
//
#ifndef GAME_SKYBOX_HPP
#define GAME_SKYBOX_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "Image.hpp"
#include "Shader.hpp"

class Skybox {
private:
    GLuint textureID;
    GLuint vao;
    GLuint vbo;
public:
    Skybox(std::vector<Image> images);
    void draw(glm::mat4 view, glm::mat4 proj, Shader& skyboxShader);
};


#endif //GAME_SKYBOX_HPP
