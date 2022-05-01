#version 460
in vec3 aPos;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;
void main()
{
    gl_Position =u_Projection*u_View*u_Model*vec4(aPos,1);
}



