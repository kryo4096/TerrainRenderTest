//
// Created by jonas on 9/26/19.
//

#include "Image.hpp"
#include <cassert>

Image::Image(const uint8_t* imageData, unsigned int width, unsigned int height) : width(width),
                                                                                   height(height), imageData(std::vector<uint8_t>(3 * width * height)) {

    Image::imageData.assign(imageData, imageData + width * height * 3 * sizeof(uint8_t));


}

glm::vec3 Image::sample(unsigned int x, unsigned int y) const {
    assert(x < width && y < height);

    auto pixelIndex = (y * width + x) * 3;

    return glm::vec3(imageData[pixelIndex + 0], imageData[pixelIndex + 1], imageData[pixelIndex + 2]);
}

const std::vector<uint8_t> &Image::getImageData() const {
    return imageData;
}

unsigned int Image::getWidth() const {
    return width;
}

unsigned int Image::getHeight() const {
    return height;
}
