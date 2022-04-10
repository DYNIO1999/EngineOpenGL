#version 400
layout (location = 0 ) in vec3 VertexPosition;
layout (location = 1) in vec2 texturePos;
out vec2 textureCords;
void main()
{
    textureCords = texturePos;
    gl_Position = vec4(VertexPosition, 1.0);
}