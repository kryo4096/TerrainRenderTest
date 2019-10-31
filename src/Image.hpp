//
// Created by jonas on 9/26/19.
//

#ifndef GAME_IMAGE_HPP
#define GAME_IMAGE_HPP


#include <vector>
#include <cstdint>
#include <glm/glm.hpp>

class Image {
    std::vector<uint8_t> imageData;
    unsigned int width, height;
public:
    Image(const uint8_t *data, unsigned int width, unsigned int height);

    glm::vec3 sample(unsigned int x, unsigned int y) const;

    const std::vector<uint8_t> &getImageData() const;

    unsigned int getWidth() const;

    unsigned int getHeight() const;
};


#endif //GAME_IMAGE_HPP
