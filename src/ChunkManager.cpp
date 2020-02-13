//
// Created by jonas on 9/25/19.
//

#include "ChunkManager.hpp"
#include "MeshBuilder.hpp"
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

template<class T>
std::vector<std::vector<T*>> create2d(int genRadius) {
    auto array = std::vector<std::vector<T*>>(0);
    for (int x = 0; x <= genRadius * 2; x++) {
        array.emplace_back(std::vector<T*>(0));
        for (int y = 0; y <= genRadius * 2; y++) {
            array[x].push_back(nullptr);
        }
    }
    return array;
}

ChunkManager::ChunkManager(IChunkGenerator &chunkGen, int genRadius) : chunkGen(chunkGen), genRadius(genRadius) {
    chunks = create2d<Mesh>(genRadius);

}

void ChunkManager::update(glm::ivec2 newCenter) {
    if (newCenter != currentCenter) {
        int deltaX = newCenter.x - currentCenter.x;
        int deltaY = newCenter.y - currentCenter.y;
        currentCenter = newCenter;
        tasks.clear();

        auto newChunks = create2d<Mesh>(genRadius);


        for(int x = 0; x <= 2 * genRadius; x++) {
            for(int y = 0; y <= 2 * genRadius; y++) {
                int oldX = x + deltaX;
                int oldY = y + deltaY;
                if(oldX >= 0 && oldX <= genRadius * 2 && oldY >= 0 && oldY <= genRadius * 2 && chunks[oldX][oldY] != nullptr) {
                    newChunks[x][y] = chunks[oldX][oldY];
                } else {
                    tasks.push_back(glm::ivec2(x,y));
                }
            }
        }

        for(int x = 0; x <= 2 * genRadius; x++) {
            for(int y = 0; y <= 2 * genRadius; y++) {
                chunks[x][y] = newChunks[x][y];
            }
        }
    }

    auto new_meshes = create2d<MeshBuilder>(genRadius);

    #pragma omp parallel for
    for (int i = 0; i < 12; i++) {
        if(i >= tasks.size()) continue;
        auto task = tasks[tasks.size() - 1 - i];
        new_meshes[task.x][task.y] = new MeshBuilder(
                chunkGen.generateChunk(task.x + currentCenter.x - genRadius, task.y + currentCenter.y - genRadius,
                                       0));
    }

    for(int i = 0; i < 12; i++) {
        if(i >= tasks.size()) continue;

        auto task = tasks[tasks.size() - 1 - i];
        chunks[task.x][task.y] = new Mesh(new_meshes[task.x][task.y]->build());
    }

    tasks.resize(tasks.size() - std::min<int>(12, tasks.size()));
}


void ChunkManager::draw() {
    for (auto &cs : chunks) {
        for (auto &c : cs) {
            if (c != nullptr) c->draw();
        }
    }
}




