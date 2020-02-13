#include "TerrainGenerator.hpp"
#include "MeshBuilder.hpp"
#include <vector>
#include <cmath>
#include "Color.hpp"

TerrainGenerator::TerrainGenerator(IHeightProvider &heightProvider, int chunkSize, glm::vec3 scale) : heightProvider(
        heightProvider), chunkSize(chunkSize), scale(scale) {}

glm::vec3 scaleV(glm::vec3 a, glm::vec3 b) {
    return glm::vec3(a.x * b.x, a.y * b.y, a.z * b.z);
}

MeshBuilder TerrainGenerator::generateChunk(int chunkX, int chunkZ, unsigned int lod)  {
    auto builder = MeshBuilder();

    auto resolution = static_cast<int>(1u << lod);

    auto scaledChunkSize = chunkSize / resolution;

    for (int vx = 0; vx <= scaledChunkSize; vx++) {
        for (int vz = 0; vz <= scaledChunkSize; vz++) {
            auto resScale = static_cast<float>(resolution);

            auto x = static_cast<float>(scaledChunkSize * chunkX + vx) * resScale;
            auto z = static_cast<float>(scaledChunkSize * chunkZ + vz) * resScale;

            auto currentPoint = scaleV(glm::vec3(x, heightProvider.getHeightAt(x, z), z), scale);
            auto rightPoint = scaleV(glm::vec3(x + 1, heightProvider.getHeightAt(x + 1, z), z),
                                     scale);
            auto upperPoint = scaleV(glm::vec3(x, heightProvider.getHeightAt(x, z + 1), z + 1),
                                     scale);

            auto normal = glm::normalize(glm::cross(upperPoint - currentPoint, rightPoint - currentPoint));

            builder.addVertex(Vertex(currentPoint, WHITE, normal, glm::vec2((vx % 2) * 2 - 1, (vz % 2) * 2 - 1)));
            worldHeight = fmax(worldHeight, currentPoint.y);
            int index = vx * (scaledChunkSize + 1) + vz;
            if (vx < scaledChunkSize && vz < scaledChunkSize) {
                std::vector<int> indices = {index, index + scaledChunkSize + 1, index + 1, index + scaledChunkSize + 1,
                                            index + scaledChunkSize + 2, index + 1};
                builder.addIndices(indices);
            }
        }
    }

    return builder;
}

int TerrainGenerator::getChunkSize() {
    return chunkSize;
}

float TerrainGenerator::getWorldHeight() const {
    return worldHeight;
}

