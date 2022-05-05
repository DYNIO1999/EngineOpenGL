#version 460
out vec4 FragColor;

in vec2 v_TextCoord;
uniform sampler2D u_Texture0;
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;

void main()
{
    vec4 snowTexel = texture(u_Texture0,v_TextCoord );
    vec4 pathTexel = texture(u_Texture1, v_TextCoord);
    vec4 pavementTexel = texture(u_Texture2, v_TextCoord);
    float pathWeight = pathTexel.r;
    float snowWeight = 1.0-pathWeight;
    FragColor =pavementTexel*pathWeight + snowTexel*snowWeight ;
}
