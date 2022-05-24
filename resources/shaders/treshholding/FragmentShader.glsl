#version 460
out vec4 FragColor;
in vec2 v_TextCoord;
uniform sampler2D u_Texture;
void main()
{
    vec4 texColor = texture(u_Texture,v_TextCoord);
    FragColor = texColor;
}