#version 460

layout ( location = 0 ) out vec4 FragColor;

//in vec2 v_TextCoord;
uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture,vec2(0.0, 0.5));
    FragColor = vec4(texColor.xyz,1.0);
}