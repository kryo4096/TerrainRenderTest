//
// Created by jonas on 9/26/19.
//

#ifndef GAME_RESOURCELOADER_HPP
#define GAME_RESOURCELOADER_HPP

#include <string>
#include <map>
#include "Image.hpp"
#include "Shader.hpp"

class ResourceLoader {
    std::string resourcePath;

    std::string prependResourcePath(const std::string& path) const;
public:
    ResourceLoader(const std::string &resourcePath);

    std::string loadTextFile(const std::string& path) const;

    Image loadImage(const std::string& path) const;

    Shader
    loadShader(const std::string &vertexPath, const std::string &fragmentPath, const std::string &geometryPath) const;

    Shader loadShader(const std::string &vertexPath, const std::string &fragmentPath) const;
};


#endif //GAME_RESOURCELOADER_HPP
