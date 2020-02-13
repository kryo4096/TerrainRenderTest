#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 vCol[];
in vec3 vNormal[];
in vec2 vUV[];
in vec4 worldPos[];
in float vDist[];

out vec3 gCol;
out vec3 gNormal;
out vec2 gUV;
out float gDist;

out vec3 triPos;
in vec3 modelPos[];

uniform float realTime;

uniform float worldHeight;

void main() {
    gNormal = normalize(vNormal[0] + vNormal[1] + vNormal[2]) / 3.0;
    triPos = ((worldPos[0] + worldPos[1] + worldPos[2]) / 3.0).xyz;

    float meanHeight = (modelPos[0].y + modelPos[1].y + modelPos[2].y) / 3;
    
    gCol = vec3(0.8, 0.8, 0.8);
    for(int i = 0; i < 3; i++) {
        gl_Position = gl_in[i].gl_Position;
        gUV = vUV[i];
        gDist = vDist[i];
        EmitVertex();
    }

    EndPrimitive();
}