#version 460
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec3 colors;
layout (location = 3) in vec2 texCords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    gl_Position = projection*view*model*vec4(aPos,1);
}