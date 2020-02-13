//
// Created by jonas on 9/24/19.
//

#ifndef GAME_LOGISTICHEIGHTPROVIDER_HPP
#define GAME_LOGISTICHEIGHTPROVIDER_HPP


#include <simplex/SimplexNoise.h>
#include "IHeightProvider.hpp"

class LogisticHeightProvider : public IHeightProvider {
    SimplexNoise noise;
    float steepness;
    float offset;
    float amplification;
public:
    LogisticHeightProvider(SimplexNoise noise, float steepness, float offset, float amplification);
    float getHeightAt(float x, float y) override;
};


#endif //GAME_LOGISTICHEIGHTPROVIDER_HPP
