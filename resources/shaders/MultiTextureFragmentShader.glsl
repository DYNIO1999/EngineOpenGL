#version 460
out vec4 FragColor;

in vec2 v_TextCoord;
uniform sampler2D u_Texture0;
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2; //mask

void main()
{
    vec4 texel0, texel1, texel2, resultColor;
    texel0 = texture2D(Texture0, TexCoord0);
    texel1 = texture2D(Texture1, TexCoord0);
    texel2 = texture2D(Texture2, TexCoord0);
    resultColor = mix(texel0, texel1, texel2.a);

    FragColor = resultColor;
}
