#version 330 core

uniform vec3 lightDirection;

out vec4 FragColor;

in vec3 gNormal;
in vec3 gCol;
in vec2 gUV;
in vec3 triPos;

void main()
{
    float diffuse = max(dot(gNormal, normalize(-lightDirection)), 0);

    vec3 matCol = gCol;

    vec3 diffuseComp =  1.2 * vec3(1.0, 1.0, 1.0) * diffuse;
    vec3 ambientComp = vec3(0.8, 0.8, 1.0) * 0.1;

    vec3 colorResult = matCol * (diffuseComp + ambientComp);

    FragColor = vec4(colorResult, 1.0);
} 