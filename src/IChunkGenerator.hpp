//
// Created by jonas on 9/25/19.
//

#ifndef GAME_ICHUNKGENERATOR_HPP
#define GAME_ICHUNKGENERATOR_HPP

#include "Mesh.hpp"


class IChunkGenerator {
public:
    virtual Mesh generateChunk(int chunkX, int chunkY, unsigned int lod) = 0;
    virtual int getChunkSize() = 0;
};


#endif //GAME_ICHUNKGENERATOR_HPP
