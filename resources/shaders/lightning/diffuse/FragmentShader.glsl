#version 460
out vec4 FragColor;
uniform vec4 u_Color;
uniform vec3 u_LightPosition;
in vec3 normal;
in vec3 currentPosition;

void main()
{
    vec4 objectColor = u_Color;
    vec3 normalizedNormal = normalize(normal);
    vec3 lightDirection = normalize(u_LightPosition - currentPosition);
    float diffuse = max(dot(normal, lightDirection), 0.0f);
    vec4  result = objectColor *diffuse; 
    FragColor = objectColor *diffuse;
}