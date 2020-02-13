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
    std::vector<std::vector<Mesh*>> chunks;
    glm::ivec2 currentCenter = glm::ivec2(-142413,-124412);
    IChunkGenerator& chunkGen;
    int genRadius;
    std::vector<glm::ivec2> tasks;
public:
    ChunkManager(IChunkGenerator &chunkGen, int radius);
    void update(glm::ivec2 newCenter);
    void draw();
};


#endif //GAME_CHUNKMANAGER_HPP
