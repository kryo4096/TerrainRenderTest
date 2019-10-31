//
// Created by jonas on 9/25/19.
//

#ifndef GAME_CHUNKMANAGER_HPP
#define GAME_CHUNKMANAGER_HPP

#include <vector>
#include <glm/glm.hpp>
#include <memory>

#include "Mesh.hpp"
#include "IChunkGenerator.hpp"

class ChunkManager {
    std::vector<std::vector<std::unique_ptr<Mesh>>> chunks;
    glm::ivec2 currentCenter = glm::ivec2(0,0);
    IChunkGenerator& chunkGen;
    int genRadius;
public:
    ChunkManager(IChunkGenerator &chunkGen, int radius);
    void update(const glm::ivec2 &newCenter);
    void draw();
};


#endif //GAME_CHUNKMANAGER_HPP
