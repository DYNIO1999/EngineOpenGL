#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texCords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 v_TextCoord;

void main()
{

    gl_Position = vec4(aPos,1);
    v_TextCoord = texCords;
}