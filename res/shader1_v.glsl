#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec3 aNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 vCol;
out vec3 vNormal;

void main() {
    vCol = aCol;
    vec4 normal = modelMatrix * vec4(aNormal, 0.0);
    vNormal = normal.xyz;
     
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
}