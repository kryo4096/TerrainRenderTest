//
// Created by jonas on 9/24/19.
//

#include "LogisticHeightProvider.hpp"

#include <cmath>
#include <simplex/SimplexNoise.h>

LogisticHeightProvider::LogisticHeightProvider(SimplexNoise noise, float steepness, float offset, float amplification) : noise(noise), steepness(steepness), offset(offset), amplification(amplification) {}

float LogisticHeightProvider::getHeightAt(float x, float y) {
    auto value = noise.fractal(8, x, y) * 2 - 1;
    return 1.0f / (1.0f + expf(-steepness*(value * amplification - offset)));
}


