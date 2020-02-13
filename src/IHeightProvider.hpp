//
// Created by jonas on 9/22/19.
//

#ifndef GAME_IHEIGHTPROVIDER_HPP
#define GAME_IHEIGHTPROVIDER_HPP


class IHeightProvider {
public:
    virtual float getHeightAt(float x, float y) = 0;
};


#endif //GAME_IHEIGHTPROVIDER_HPP
