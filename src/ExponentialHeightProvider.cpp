//
// Created by jonas on 9/23/19.
//

#include "ExponentialHeightProvider.hpp"
#include <cmath>

ExponentialHeightProvider::ExponentialHeightProvider(SimplexNoise noise, float exponentFactor, float amplitude,
                                                     float offset) : noise(noise), exponentFactor(exponentFactor),
                                                                     amplitude(amplitude), offset(offset) {}

float ExponentialHeightProvider::getHeightAt(float x, float z) {
    float value = amplitude * exp(noise.fractal(8, x, z) * exponentFactor - offset);
    return value;
}


