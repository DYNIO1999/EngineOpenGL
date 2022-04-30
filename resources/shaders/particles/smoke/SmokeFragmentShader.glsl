#version 460
out vec4 FragColor;
uniform vec4 u_Color;
in float Transp;

void main()
{
    FragColor = u_Color;
    FragColor.a *= Transp;
}


