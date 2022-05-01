#version 460
out vec4 FragColor;
in vec2 uv;

uniform sampler2D u_Texture;
void main()
{
    vec4 texColor = texture(u_Texture,uv);
    //texColor.a *= 0.1;
    texColor.a *= 0.5;
    FragColor = texColor;
}


