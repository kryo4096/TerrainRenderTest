#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 vCol[];
in vec3 vNormal[];

out vec3 gCol;
out vec3 gNormal;

uniform float realTime;

void main() {

    gNormal = normalize(vNormal[0] + vNormal[1] + vNormal[2]) / 3.0;

    for(int i = 0; i < 3; i++) {
        gl_Position = gl_in[i].gl_Position;
        gCol = vCol[i];
        EmitVertex();
    }

    EndPrimitive();
}