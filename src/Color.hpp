#ifndef COLOR_HPP
#define COLOR_HPP

#define RED vec3(1.0f,0.0f,0.0f)
#define GREEN vec3(0.0f, 1.0f, 0.0f)
#define BLUE vec3(0.0f, 0.0f, 1.0f)

#define YELLOW vec3(1.0f, 1.0f,0.0f)
#define CYAN vec3(0.0f, 1.0f, 1.0f)
#define MAGENTA vec3(1.0f, 0.0f, 1.0f)

#define BLACK vec3(0.0f, 0.0f, 0.0f)
#define WHITE vec3(1.0f, 1.0f, 1.0f)

#define RGB(r,g,b) glm::vec3(r/256.0f, g / 256.0f, b/256.0f)

#endif