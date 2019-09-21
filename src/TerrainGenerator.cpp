#include "TerrainGenerator.hpp"
#include "MeshBuilder.hpp"
#include <vector>

#define OCTAVE_COUNT 8

TerrainGenerator::TerrainGenerator(SimplexNoise noise, int chunkSize, glm::vec3 scale) : mNoise(noise), mChunkSize(chunkSize), mScale(scale) {}

glm::vec3 scale(glm::vec3 a, glm::vec3 b) {
    return glm::vec3(a.x * b.x, a.y * b.y, a.z * b.z);
}

Mesh TerrainGenerator::generateChunk(int chunkX, int chunkZ) {
    auto builder = MeshBuilder();

    for(int vx = 0; vx <= mChunkSize; vx++) {
        for(int vz = 0; vz <= mChunkSize; vz++) {

            float x = static_cast<float>(mChunkSize * chunkX + vx);
            float z = static_cast<float>(mChunkSize * chunkZ + vz);
            
            auto currentPoint = scale(glm::vec3(x, mNoise.fractal(OCTAVE_COUNT, x, z), z), mScale);
            auto rightPoint = scale(glm::vec3(x + 1, mNoise.fractal(OCTAVE_COUNT, x + 1, z), z), mScale);
            auto upperPoint = scale(glm::vec3(x, mNoise.fractal(OCTAVE_COUNT, x, z + 1), z + 1), mScale);

            auto normal = glm::normalize(glm::cross(upperPoint - currentPoint, rightPoint - currentPoint));

            builder.addVertex(Vertex(currentPoint, glm::vec3(1,1,1), normal));
            
            int index = vx * (mChunkSize + 1) + vz;
            if(vx < mChunkSize && vz < mChunkSize) {
                std::vector<int> indices = {index, index + mChunkSize + 1, index + 1, index + mChunkSize + 1, index + mChunkSize + 2, index + 1};
                builder.addIndices(indices);
            } 
        }
    }

    return builder.build();
}