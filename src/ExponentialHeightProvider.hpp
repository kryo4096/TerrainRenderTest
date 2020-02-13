//
// Created by jonas on 9/23/19.
//

#include "IHeightProvider.hpp"
#include "simplex/SimplexNoise.h"

#ifndef GAME_EXPONENTIALHEIGHTPROVIDER_HPP
#define GAME_EXPONENTIALHEIGHTPROVIDER_HPP


class ExponentialHeightProvider : public IHeightProvider {
    SimplexNoise noise;
    float exponentFactor;
    float amplitude;
    float offset;
public:
    ExponentialHeightProvider(SimplexNoise noise, float exponentFactor, float amplitude, float offset);
    float getHeightAt(float x, float z) override;
};


#endif //GAME_EXPONENTIALHEIGHTPROVIDER_HPP
