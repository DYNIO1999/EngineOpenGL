#version 460
out vec4 FragColor;
uniform vec4 u_Color;
uniform vec4 u_AmbientLightColor;
uniform float u_AmbientIntensity;
void main()
{
    vec4 objectColor = u_Color;
    vec4 ambient =  u_AmbientIntensity* u_AmbientLightColor;
    vec4 result = objectColor* ambient;
    FragColor = result;
}