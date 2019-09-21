#version 330 core

uniform float realTime;

out vec4 FragColor;

in vec3 gNormal;
in vec3 gCol;


const vec3 AMBIENT = vec3(0.5,0.6,0.8);
const vec3 SPECULAR = vec3(1.0,1.0,1.0);

void main()
{
    float time = realTime / 60;
    vec3 diffuse1 = vec3(0.7, 0.0, 1.0) * max(dot(gNormal, normalize(vec3(cos(time), sin(time), sin(time)))), 0);
    vec3 diffuse2 = vec3(1.0, 0.5, 0.0) * max(dot(gNormal, normalize(vec3(cos(time), cos(time), sin(time)))), 0);
    vec3 diffuse3 = vec3(1.0, 1.0, 1.0) * max(dot(gNormal, normalize(vec3(cos(time), -sin(time), sin(time)))), 0);
    vec3 diffuse4 = vec3(0.0, 1.0, 1.0) * max(dot(gNormal, normalize(vec3(cos(time), -cos(time), sin(time)))), 0);
    vec3 ambient = vec3(0.6, 0.6, 1.0) * sin(time);

    vec3 light = ambient * 0.1 + diffuse1 + diffuse2 + diffuse3 + diffuse4;

    FragColor = vec4(gCol * light,1.0);
} 