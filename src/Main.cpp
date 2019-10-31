#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <cmath>

#include "Shader.hpp"
#include "Transform.hpp"
#include "Mesh.hpp"
#include "Vertex.hpp"
#include "Color.hpp"
#include "InputManager.hpp"
#include "MeshBuilder.hpp"
#include "TerrainGenerator.hpp"

#include "simplex/SimplexNoise.h"
#include "ExponentialHeightProvider.hpp"
#include "LogisticHeightProvider.hpp"
#include "ResourceLoader.hpp"
#include "ChunkManager.hpp"

#include <glm/gtx/string_cast.hpp>

using namespace glm;
using namespace std;

int g_width = 1280;
int g_height = 720;

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    g_width = width > 0 ? width : 1;
    g_height = height > 0 ? height : 1;
    glViewport(0, 0, width, height);

    std::cout << "Resized to: (" << g_width << ", " << g_height << ")\n";
}

const auto AXIS_HORIZONTAL = 0;
const auto AXIS_VERTICAL = 1;
const auto BUTTON_ESCAPE = 2;

class App {
    GLFWwindow *window;
    InputManager inputManager;

public:
    App() {
        initGL();
        inputManager = InputManager(window);
        inputManager.addAxis(AXIS_HORIZONTAL, GLFW_KEY_A, GLFW_KEY_D);
        inputManager.addAxis(AXIS_VERTICAL, GLFW_KEY_S, GLFW_KEY_W);
        inputManager.addAxis(BUTTON_ESCAPE, GLFW_KEY_UNKNOWN, GLFW_KEY_ESCAPE);
        inputManager.setMouseSensitivity(200);
        start();
    }

    void initGL() {
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow *w = glfwCreateWindow(g_width, g_height, "GL Learn", NULL, NULL);


        glfwMakeContextCurrent(w);

        glewExperimental = true;

        glewInit();

        glfwSetFramebufferSizeCallback(w, framebuffer_size_callback);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_FRAMEBUFFER_SRGB);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);

        this->window = w;
    }

    void start() {
        ResourceLoader loader("res");
        auto shader = loader.loadShader("default.vsh", "default.fsh", "default.glsl");

        Transform transform;
        Transform camera;

        camera.setPosition(vec3(0, 10, 0));

        SimplexNoise noise(0.003, 1.0, 4.0, 0.25);
        LogisticHeightProvider heightProvider(noise, 2, 0, 1);
        TerrainGenerator terrainGen(heightProvider, 64, vec3(1, 100, 1));
        //ChunkManager manager(terrainGen, 10);

        vector<Mesh *> chunks;

        const int WORLD_SIZE = 16;

        for (int x = -WORLD_SIZE / 2; x <= WORLD_SIZE / 2; x++) {
            for (int z = -WORLD_SIZE / 2; z <= WORLD_SIZE / 2; z++) {
                chunks.push_back(new Mesh(terrainGen.generateChunk(x, z,  2 + (x + z) / 20)));
            }
        }

        float lookX = 0;
        float lookY = 1;

        auto lastFrame = glfwGetTime();
        auto delta = 0.0f;

        auto image = loader.loadImage("terrainColor.png");

        glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, image.getWidth(), image.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image.getImageData().data());
        glGenerateMipmap(GL_TEXTURE_2D);

        while (!glfwWindowShouldClose(window)) {
            inputManager.update();

            lookX = lookX - inputManager.getMouseDelta().x;
            lookY = lookY - inputManager.getMouseDelta().y;

            if(inputManager.getAxis(BUTTON_ESCAPE) > 0) {
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            }

            camera.setRotation(angleAxis(radians(lookY), vec3(1.0f, 0.0f, 0.0f)));
            camera.rotate(angleAxis(radians(lookX), vec3(0.0f, 1.0f, 0.0f)));

            camera.translateLocal(
                    glm::vec3(inputManager.getAxis(AXIS_HORIZONTAL), 0, -inputManager.getAxis(AXIS_VERTICAL)) * delta *
                    50.0f);

            glm::mat4 projectionMatrix = glm::perspective(radians(60.0f), (float) g_width / (float) g_height, 0.1f,
                                                          10000.0f);

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            shader.setFloat("realTime", glfwGetTime());
            shader.setFloat("worldHeight", terrainGen.getWorldHeight());
            shader.setMat4("modelMatrix", transform.matrix());
            shader.setMat4("viewMatrix", camera.inverseMatrix());
            shader.setMat4("projectionMatrix", projectionMatrix);
            shader.setVec3("lightDirection", glm::vec3(1.0, -1.0, 0.3));
            shader.use();

            for (auto const &chunk : chunks) {
                chunk->draw();
            }

            glfwSwapBuffers(window);
            glfwPollEvents();

            do {
                delta = glfwGetTime() - lastFrame;
            } while (delta < 0.01f);

            lastFrame = glfwGetTime();
        }

        glfwTerminate();
    }
};


int main() {
    App app;

    return 0;
}

