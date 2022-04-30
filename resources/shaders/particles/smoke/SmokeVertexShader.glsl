#version 460
in vec3 aPos;
uniform mat4 u_MVP;

void main()
{
    gl_Position =u_MVP* vec4(aPos,1);
}



