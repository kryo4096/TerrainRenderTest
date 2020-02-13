#version 330 core

uniform vec3 lightDirection;

out vec4 FragColor;

in vec3 gNormal;
in vec3 gCol;
in vec2 gUV;
in vec3 triPos;
in float gDist;

void main()
{
    float diffuse = max(dot(gNormal, normalize(-lightDirection)), 0);

    vec3 matCol = vec3(1.0, 1.0, 1.0);

    vec3 diffuseComp =  vec3(0.2, 1.0, 0.4) * diffuse ;
    vec3 ambientComp = vec3(0.0, 1.0, 0.0) * 0.01;

    FragColor = vec4(matCol * (diffuseComp + ambientComp), 1.0);
} 