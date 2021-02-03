#version 330 core

in vec3 fPosition;
in vec3 fNormal;

out vec4 outcolor;

uniform samplerCube skybox;
uniform vec3 camera_pos;

uniform int is_reflection;
uniform float index;

void main()
{   
    // Environment map
    vec3 I = normalize(fPosition - camera_pos);
    vec3 R;
    if (is_reflection == 1)
        R = reflect(I, normalize(fNormal));
    else
        R = refract(I, normalize(fNormal), index);

    outcolor = vec4(texture(skybox, R).rgb, 1.0);
}
