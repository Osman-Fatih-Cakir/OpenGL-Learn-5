#version 330 core

in vec3 fPosition;
in vec3 fNormal;

out vec4 outcolor;

uniform samplerCube skybox;
uniform vec3 camera_pos;

void main()
{   
    // Environment map
    vec3 I = normalize(fPosition - camera_pos);
    vec3 R = reflect(I, normalize(fNormal));

    outcolor = vec4(texture(skybox, R).rgb, 1.0);
}
