#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <map>

struct Axis {
public:
    int negativeKey;
    int positiveKey;
    float value;
};

class InputManager {
    GLFWwindow *window;
    std::map<int, Axis> axes;
    float mouseX;
    float mouseY;
    float mouseSensitivity = 1.0f;

public:
    explicit InputManager(GLFWwindow *mWindow);

    InputManager();

    void addAxis(int id, int negativeKey, int positiveKey);

    float getAxis(int id);

    glm::vec2 getMouseDelta();

    float getMouseSensitivity() const;

    void setMouseSensitivity(float mouseSensitivity);

    void update();
};

#endif

