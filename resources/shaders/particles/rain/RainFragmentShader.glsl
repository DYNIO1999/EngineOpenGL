#version 460
layout ( location = 0 ) out vec4 FragColor;

uniform vec4 u_Color;
in vec2 uv;
void main()
{
    FragColor = u_Color;
}