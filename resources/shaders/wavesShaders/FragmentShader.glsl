#version 400
layout ( location = 0 ) out vec4 FragColor;
in vec2 textureCords;
uniform vec4 LineColor;
uniform sampler2D u_Texture;
in vec2 texTestCord;

void main()
{
    vec4 texColor = texture(u_Texture,texTestCord).rgba;
    FragColor = vec4(texColor.x, texColor.y, texColor.z, 0.0f);
}