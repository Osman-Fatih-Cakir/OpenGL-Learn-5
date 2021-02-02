#version 330 core

in vec3 fTexCoord;

out vec4 outcolor;

uniform samplerCube skybox;

void main()
{    
    outcolor = texture(skybox, fTexCoord);
}