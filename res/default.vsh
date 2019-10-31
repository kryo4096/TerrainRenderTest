#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aUV;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 vCol;
out vec3 vNormal;
out vec2 vUV;

out vec4 worldPos;

out vec3 modelPos;

void main() {
    vCol = aCol;
    vec4 normal = modelMatrix * vec4(aNormal, 0.0);
    vNormal = normal.xyz;
    vUV = aUV;

    modelPos = aPos;

    worldPos = modelMatrix * vec4(aPos, 1.0);
     
    gl_Position = projectionMatrix * viewMatrix * worldPos;
}