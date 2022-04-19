#version 460
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


//out vec2 v_TextCoord;

void main()
{
  ///  v_TextCoord = texCoords[];

    gl_Position =projection* view * model* vec4(aPos,1);
}