#version 330 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;

out vec3 fNormal;
out vec3 fPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 normal_matrix;

void main()
{
    gl_Position = projection * view * model * vec4(vPos, 1.0);

    fNormal = mat3(transpose(inverse(model))) * vNormal;
    fPosition = (model * vec4(vPos, 1.0)).xyz;
}
