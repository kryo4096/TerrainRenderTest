#include "InputManager.hpp"

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

InputManager::InputManager(GLFWwindow *mWindow) : window(mWindow) {}
