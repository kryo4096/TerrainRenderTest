#include "InputManager.hpp"
#include <cmath>

int clamp(int i) {
    if(i < -1) {
        return -1;
    }
    
    if(i > 1) {
        return 1;
    }

    return i;
}

void InputManager::update() {
    /* Handle Keyboard Input */
    for(auto& [id, axis] : axes) {

        auto pos = glfwGetKey(window, axis.positiveKey);
        if(pos == GLFW_PRESS) {
            axis.value = clamp(axis.value + 1);
        } else if(pos == GLFW_RELEASE && axis.value > 0) {
            axis.value = clamp(axis.value - 1);
        }

        auto neg = glfwGetKey(window, axis.negativeKey);
        if(neg == GLFW_PRESS) {
            axis.value = clamp(axis.value - 1);
        } else if(neg == GLFW_RELEASE && axis.value < 0) {
            axis.value = clamp(axis.value + 1);
        }
    }

    /* Handle Mouse Input */
    double cursorX, cursorY;
    glfwGetCursorPos(window, &cursorX, &cursorY);

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    double centerX = static_cast<double>(screenWidth) / 2.0;
    double centerY = static_cast<double>(screenHeight) / 2.0;
    glfwSetCursorPos(window, centerX, centerY);

    float screenScale = 1 / sqrt(pow(static_cast<float>(screenWidth), 2) + pow(static_cast<float>(screenHeight), 2));

    mouseX = static_cast<float>(cursorX - centerX) * screenScale;
    mouseY = static_cast<float>(cursorY - centerY) * screenScale;
}

void InputManager::addAxis(int id, int negativeKey, int positiveKey) {
    Axis axis;
    axis.negativeKey = negativeKey;
    axis.positiveKey = positiveKey;
    axes[id] = axis;
}

float InputManager::getAxis(int i) {
    return axes[i].value;
}

InputManager::InputManager(GLFWwindow *window) : window(window) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

glm::vec2 InputManager::getMouseDelta() {
    return glm::vec2(mouseX, mouseY) * mouseSensitivity;
}

InputManager::InputManager() {
    window = nullptr;
}

float InputManager::getMouseSensitivity() const {
    return mouseSensitivity;
}

void InputManager::setMouseSensitivity(float mouseSensitivity) {
    InputManager::mouseSensitivity = mouseSensitivity;
}

glm::vec2 getAxis2d(int id) {
    return glm::vec2();
}
