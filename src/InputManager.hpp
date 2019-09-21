#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <GLFW/glfw3.h>
#include <map>

struct Axis {
public:
    int negativeKey;
    int positiveKey;
    float value;
};

class InputManager {
    GLFWwindow* window;
    std::map<int, Axis> axes;
    
public: 
    explicit InputManager(GLFWwindow *mWindow);
    void addAxis(int id, int negativeKey, int positiveKey);
    float getAxis(int id);

    void update();
};

#endif

