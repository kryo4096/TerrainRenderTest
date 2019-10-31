//
// Created by jonas on 9/23/19.
//

#include "ExponentialHeightProvider.hpp"
#include <cmath>

ExponentialHeightProvider::ExponentialHeightProvider(SimplexNoise noise, float exponentFactor, float amplitude) : noise(noise), exponentFactor(exponentFactor), amplitude(amplitude){}

float ExponentialHeightProvider::getHeightAt(float x, float z) {
    float value = amplitude * exp(noise.fractal(8, x, z) * exponentFactor);
    return value;
}


