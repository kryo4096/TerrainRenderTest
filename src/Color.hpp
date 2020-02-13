#ifndef COLOR_HPP
#define COLOR_HPP

#define RED glm::vec3(1.0f,0.0f,0.0f)
#define GREEN glm:::vec3(0.0f, 1.0f, 0.0f)
#define BLUE glm::vec3(0.0f, 0.0f, 1.0f)

#define YELLOW glm::vec3(1.0f, 1.0f,0.0f)
#define CYAN glm::vec3(0.0f, 1.0f, 1.0f)
#define MAGENTA glm::vec3(1.0f, 0.0f, 1.0f)

#define BLACK glm::vec3(0.0f, 0.0f, 0.0f)
#define WHITE glm::vec3(1.0f, 1.0f, 1.0f)

#define RGB(r,g,b) glm::vec3(r/256.0f, g / 256.0f, b/256.0f)

#endif