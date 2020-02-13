//
// Created by jonas on 9/26/19.
//

#include "ResourceLoader.hpp"

#include <cassert>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/image.h"

ResourceLoader::ResourceLoader(const std::string &resourcePath) : resourcePath(resourcePath) {}

Image ResourceLoader::loadImage(const std::string& path) const {
    int w, h, n;

    auto concatPath = prependResourcePath(path);

    auto data = stbi_load(concatPath.c_str(), &w, &h, &n, 3);

    Image image(data, w, h);

    stbi_image_free(data);

    return image;
}

Shader ResourceLoader::loadShader(const std::string &vertexPath, const std::string &fragmentPath) const {
    std::string vertexSource, fragmentSource;

    try {
        vertexSource = loadTextFile(vertexPath);
        fragmentSource = loadTextFile(fragmentPath);
    }
    catch(std::ifstream::failure& e) {
        std::cout << "Failed reading shader file." << std::endl;
    }

    return Shader(vertexSource, fragmentSource);
}

Shader ResourceLoader::loadShader(const std::string &vertexPath, const std::string &fragmentPath, const std::string &geometryPath) const {
    std::string vertexSource, fragmentSource, geometrySource;

    try {
        vertexSource = loadTextFile(vertexPath);
        fragmentSource = loadTextFile(fragmentPath);
        geometrySource = loadTextFile(geometryPath);
    }
    catch(std::ifstream::failure& e) {
        std::cout << "Failed reading shader file." << std::endl;
    }

    return Shader(vertexSource, fragmentSource, geometrySource);
}


std::string ResourceLoader::loadTextFile(const std::string &path) const {
    std::ifstream file;

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    file.open(prependResourcePath(path));
    std::stringstream stream;
    stream << file.rdbuf();
    return stream.str();
}

std::string ResourceLoader::prependResourcePath(const std::string &path) const {
    return resourcePath + "/" + path;
}

const std::vector<std::string> faces
{
    "right.png",
    "left.png",
    "top.png",
    "bottom.png",
    "front.png",
    "back.png"
};

Skybox ResourceLoader::loadSkybox(const std::string &skyboxName) const {
    std::vector<Image> imgs{};
    
    for(auto& face : faces) {
        imgs.push_back(loadImage(skyboxName + "_" + face));
    }

    return Skybox(imgs);
}

