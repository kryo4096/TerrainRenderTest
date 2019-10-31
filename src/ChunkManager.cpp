//
// Created by jonas on 9/25/19.
//

#include "ChunkManager.hpp"
#include <cmath>

ChunkManager::ChunkManager(IChunkGenerator &chunkGen, int radius) : chunkGen(chunkGen), genRadius(radius){

    chunks.resize(2 * radius + 1);

    for(int i = -radius; i <= radius; i++) {
        chunks[i] = std::vector<std::unique_ptr<Mesh>>(2 * radius + 1);
    }

}

int len(const glm::ivec2& x) {
    return static_cast<int>(std::abs(x.x) + std::abs(x.y));
}

void ChunkManager::update(const glm::ivec2 &newCenter) {
    if(newCenter == currentCenter) {
        return;
    }

    for(int x = -genRadius; x <= genRadius; x++) {
        for(int y = -genRadius; y <= genRadius; y++) {
            if (len(glm::ivec2(x,y) - newCenter) > genRadius) {
                //delete chunks[x][y];
            }
        }
    }

    for(int x = -genRadius; x <= genRadius; x++) {
        for (int y = -genRadius; y <= genRadius; y++) {
            auto coord = glm::ivec2(x,y);
            if(len(coord) <= genRadius) {
                coord += currentCenter;

                if(!chunks[coord.x][coord.y]) {
                    auto chunk = std::make_unique<Mesh>(Mesh(chunkGen.generateChunk(coord.x, coord.y, 0)));
                    chunks[coord.x][coord.y] = std::move(chunk);
                }
            }
        }
    }

    ChunkManager::currentCenter = newCenter;
}

void ChunkManager::draw() {
    for(auto& cs : chunks) {
        for(auto& c : cs) {
            c.get()->draw();
        }
    }
}




