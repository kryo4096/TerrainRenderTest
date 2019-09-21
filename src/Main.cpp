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

#include <glm/gtx/string_cast.hpp>

using namespace glm;
using namespace std;

int g_width = 1280;
int g_height = 720;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    g_width = width > 0 ? width : 1;
    g_height = height > 0 ? height : 1;
    glViewport(0, 0, width, height);

    std::cout << "Resized to: (" << g_width << ", " << g_height << ")\n";
} 

#define AXIS_HORIZONTAL 0
#define AXIS_VERTICAL 1

class App {
    GLFWwindow* window;
    InputManager inputManager;

    public:
    App() : inputManager(InputManager(nullptr)){
        initGL();
        inputManager = InputManager(window);
        inputManager.addAxis(AXIS_HORIZONTAL, GLFW_KEY_A, GLFW_KEY_D);
        inputManager.addAxis(AXIS_VERTICAL, GLFW_KEY_S, GLFW_KEY_W);
        start();
    }

    void processInput() {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
            glfwSetWindowShouldClose(window, true);


    }

    void initGL() {
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow* w = glfwCreateWindow(g_width, g_height, "GL Learn", NULL, NULL);



        glfwMakeContextCurrent(w);

        glewExperimental = true;

        glewInit();

        glfwSetFramebufferSizeCallback(w, framebuffer_size_callback);

        glEnable(GL_DEPTH_TEST);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
       
        this->window = w;
    }

    void start() {
        Shader shader("res/shader1_v.glsl", "res/shader1_f.glsl","res/shader1_g.glsl");

        Transform transform;

        Transform camera;
        camera.setPosition(vec3(0,10,0));
        camera.setRotation(angleAxis(radians(0.0f), vec3(1.0f, 0.0f, 0.0f)));
        
        auto noise = SimplexNoise(0.01, 1.0, 4.0, 0.25);

        auto terrainGen = TerrainGenerator(noise, 64, vec3(1,10,1));

        vector<Mesh> chunks = vector<Mesh>();

        for(int x = -4; x <= 4; x++) {
            for (int z = -4; z <= 4; z++) {
                chunks.push_back(terrainGen.generateChunk(x,z));
            }
        }

        auto lastFrame = glfwGetTime();
        auto delta = 0.0f;

        while(!glfwWindowShouldClose(window)) {
            processInput();
            inputManager.update();

            camera.translate(glm::vec3(inputManager.getAxis(AXIS_HORIZONTAL), 0, -inputManager.getAxis(AXIS_VERTICAL)) * delta * 10.0f);

            glm::mat4 projectionMatrix = glm::perspective(radians(60.0f), (float) g_width / (float) g_height, 0.1f, 10000.0f);

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            shader.setFloat("realTime", glfwGetTime());
            shader.setMat4("modelMatrix", transform.matrix());
            shader.setMat4("viewMatrix", camera.inverseMatrix());
            shader.setMat4("projectionMatrix", projectionMatrix);
            shader.use();

            for(auto const& chunk : chunks) {
                chunk.draw();
            }

            glfwSwapBuffers(window);
            glfwPollEvents();  

            do {
                delta = glfwGetTime() - lastFrame;
            } while(delta < 0.01f);

            lastFrame = glfwGetTime();
        }

        glfwTerminate();
    }
};
 

int main() {
    App app;
    
    return 0;
}

