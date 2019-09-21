#ifndef TERRAIN_GENERATOR_HPP
#define TERRAIN_GENERATOR_HPP

#include "simplex/SimplexNoise.h"
#include "glm/glm.hpp"
#include "Mesh.hpp"

class TerrainGenerator {
    SimplexNoise mNoise;
    int mChunkSize;
    glm::vec3 mScale;
public:
    TerrainGenerator(SimplexNoise noise, int chunkSize, glm::vec3 scale);
    Mesh generateChunk(int x, int y);
};

#endif