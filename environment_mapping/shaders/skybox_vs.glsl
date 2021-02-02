#version 330 core

layout (location = 0) in vec3 vPos;

out vec3 fTexCoord;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    fTexCoord = vPos;
    vec4 pos = projection * view * vec4(vPos, 1.0);
    gl_Position = pos.xyww; // The skybox will always has the maximum depth value
}  