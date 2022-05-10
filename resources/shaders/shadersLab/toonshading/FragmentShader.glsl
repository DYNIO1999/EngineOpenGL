#version 460
out vec4 FragColor;
uniform float u_AmbientIntensity;

uniform vec3 u_Color;
uniform vec3 u_LightColor;
uniform vec3 u_LightPosition;
uniform int u_Levels = 3;

in vec3 normal;
in vec3 currentPosition;

void main()
{
    float scaleFactor = 1.0 / u_Levels;
    vec3 ambient = u_AmbientIntensity *u_LightColor;
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(u_LightPosition - currentPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = u_LightColor * floor(diff*u_Levels)*scaleFactor;
    vec3 result = (ambient + diffuse) * u_Color;
    FragColor = vec4(result, 1.0);
}