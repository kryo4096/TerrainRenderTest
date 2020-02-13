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

int g_width = 2560;
int g_height = 1440;

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    g_width = width > 0 ? width : 1;
    g_height = height > 0 ? height : 1;
    glViewport(0, 0, width, height);

    std::cout << "Resized to: (" << g_width << ", " << g_height << ")\n";
}


void APIENTRY glDebugOutput(const GLenum source, 
                            const GLenum type, 
                            const GLuint id, 
                            const GLenum severity, 
                            const GLsizei length, 
                            const GLchar *message, 
                            const void *userParam)
{
    // ignore non-significant error/warning codes
    if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return; 

    std::cout << "---------------" << std::endl;
    std::cout << "Debug message (" << id << "): " <<  message << std::endl;

    switch (source)
    {
        case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
    } std::cout << std::endl;

    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break; 
        case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
    } std::cout << std::endl;
    
    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
    } std::cout << std::endl;
    std::cout << std::endl;
    
}

const auto AXIS_HORIZONTAL = 0;
const auto AXIS_VERTICAL = 1;
const auto BUTTON_ESCAPE = 2;
const auto BUTTON_JUMP = 3;

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
        inputManager.addAxis(BUTTON_JUMP, GLFW_KEY_UNKNOWN, GLFW_KEY_SPACE);
        inputManager.setMouseSensitivity(200);
        start();
    }

    void initGL() {
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);  

        GLFWwindow *w = glfwCreateWindow(g_width, g_height, "GL Learn", glfwGetPrimaryMonitor(), NULL);

        glfwMakeContextCurrent(w);

        glewExperimental = true;

        glewInit();

        glfwSetFramebufferSizeCallback(w, framebuffer_size_callback);

        GLint flags; 
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
        {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
            glDebugMessageCallback(glDebugOutput, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE); 
        }

        this->window = w;
    }

    void start() {
        ResourceLoader loader("res");

        auto shader = loader.loadShader("default.vs", "default.fs", "default.gs");
        auto skyboxShader = loader.loadShader("skybox/skybox.vs", "skybox/skybox.fs");
        auto skybox = loader.loadSkybox("skybox/galaxy");
        auto bloomShader = loader.loadShader("bloom.vs", "bloom.fs");

        Transform transform;
        Transform camera;

        camera.setPosition(vec3(0, 10, 0));

        SimplexNoise noise(0.0001, 0.1, 4.0, 0.25);
        LogisticHeightProvider heightProvider(noise, 1.2, -1.0, 1000);
        TerrainGenerator terrainGen(heightProvider, 32, vec3(1, 1, 1));
        ChunkManager manager(terrainGen, 24);

        float lookX = 0;
        float lookY = 0;

        auto lastFrame = glfwGetTime();
        auto delta = 0.0f;

        float height;
        float yVel;

        GLuint screenQuadVAO;
        GLuint screenQuadVBO;
        GLuint screenQuadUVBO;

        float quadVertices[] = {
            1.0, -1.0,
            -1.0, -1.0,
            1.0, 1.0,
            -1.0, -1.0,
            -1.0, 1.0,
            1.0, 1.0
        };

        glGenVertexArrays(1, &screenQuadVAO);
        glGenBuffers(1, &screenQuadVBO);

        glBindVertexArray(screenQuadVAO);

        glBindBuffer(GL_ARRAY_BUFFER, screenQuadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);
        glEnableVertexAttribArray(0);

        unsigned int framebuffer;
        glGenFramebuffers(1, &framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

        // generate texture
        unsigned int texColorBuffer;
        glGenTextures(1, &texColorBuffer);

        glBindTexture(GL_TEXTURE_2D, texColorBuffer);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, g_width, g_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glBindTexture(GL_TEXTURE_2D, 0);

        // attach it to currently bound framebuffer object
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

        unsigned int rbo;
        glGenRenderbuffers(1, &rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, g_width, g_height);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);

        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);






        while (!glfwWindowShouldClose(window)) {

            inputManager.update();

            lookX = lookX - inputManager.getMouseDelta().x;
            lookY = lookY - inputManager.getMouseDelta().y;

            if(lookY < -80.0f) lookY = -80.0f;
            if(lookY > 80.0f) lookY = 80.0f;

            if(inputManager.getAxis(BUTTON_ESCAPE) > 0) {
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            }

            camera.setRotation(angleAxis(radians(lookY), vec3(1.0f, 0.0f, 0.0f)));
            camera.rotate(angleAxis(radians(lookX), vec3(0.0f, 1.0f, 0.0f)));
            
            {
                glm::vec3 in  {inputManager.getAxis(AXIS_HORIZONTAL),0 ,-inputManager.getAxis(AXIS_VERTICAL)};

                camera.translateLocalNormalizedInPlane(in * 22.0f * delta, glm::vec3(0,1.0,0.0));

            }

            float player_x = camera.getPosition().x / terrainGen.getChunkSize();
            float player_z = camera.getPosition().z / terrainGen.getChunkSize();

            float xx = camera.getPosition().x;
            float zz = camera.getPosition().z;

            float targetHeight = heightProvider.getHeightAt(xx,zz) + 2.0f;

            if(height > targetHeight) {
                yVel -= 30.0f * delta;
            } else {
                yVel = 0;
                height = targetHeight;
            }


            if(inputManager.getAxis(BUTTON_JUMP) > 0.0 && (height - targetHeight) < 1.0f) {
                yVel = 10.0f;
            }

            
            height += yVel * delta;

            camera.setPosition(glm::vec3(xx, height, zz));

            glm::mat4 projectionMatrix = glm::perspective(radians(60.0f), (float) g_width / (float) g_height, 0.1f, 10000.0f);

            glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_FRAMEBUFFER_SRGB);

            glEnable(GL_CULL_FACE);
            glCullFace(GL_FRONT);


            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

            skybox.draw(camera.inverseMatrix(), projectionMatrix, skyboxShader);
            
            shader.use();
            shader.setVec3("playerPosition", camera.getPosition());
            shader.setFloat("realTime", glfwGetTime());
            shader.setFloat("worldHeight", terrainGen.getWorldHeight());
            shader.setMat4("modelMatrix", transform.matrix());
            shader.setMat4("viewMatrix", camera.inverseMatrix());
            shader.setMat4("projectionMatrix", projectionMatrix);
            shader.setVec3("lightDirection", glm::vec3(1.0, -1.0, 0.3));
            
            manager.update(glm::ivec2((int) player_x, (int) player_z));
            manager.draw();

            glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
            glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);




            bloomShader.use();
            glBindVertexArray(screenQuadVAO);
            glDisable(GL_DEPTH_TEST);
            glBindTexture(GL_TEXTURE_2D, texColorBuffer);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            glfwSwapBuffers(window);
            glfwPollEvents();

            delta = glfwGetTime() - lastFrame;

            lastFrame = glfwGetTime();
        }

        glDeleteFramebuffers(1, &framebuffer);
        glfwTerminate();
    }
};


int main() {
    App app;

    return 0;
}

