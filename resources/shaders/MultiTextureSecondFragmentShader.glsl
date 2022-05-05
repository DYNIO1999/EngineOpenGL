#version 460
out vec4 FragColor;

in vec2 v_TextCoord;
uniform sampler2D u_Texture0;
uniform sampler2D u_Texture1;

void main()
{
    vec4 texColor1 = texture(u_Texture0,v_TextCoord);
    vec4 texColor2 = texture(u_Texture1, v_TextCoord);
    FragColor =texColor1 * mix(texColor2, vec4(1.0), 0.9);
}
