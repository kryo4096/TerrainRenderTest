#ifndef TERRAIN_GENERATOR_HPP
#define TERRAIN_GENERATOR_HPP

#include "simplex/SimplexNoise.h"
#include "glm/glm.hpp"
#include "Mesh.hpp"
#include "IHeightProvider.hpp"
#include "IChunkGenerator.hpp"
#include "MeshBuilder.hpp"

#include <memory>

class TerrainGenerator : public IChunkGenerator {
    IHeightProvider& heightProvider;
    int chunkSize;
    glm::vec3 scale;
    float worldHeight;
public:
    TerrainGenerator(IHeightProvider& heightProvider, int chunkSize, glm::vec3 scale);
    MeshBuilder generateChunk(int x, int y, unsigned int resolution) override;

    int getChunkSize() override;

    float getWorldHeight() const;
};

#endif