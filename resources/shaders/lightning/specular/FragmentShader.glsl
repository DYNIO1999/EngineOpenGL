#version 460
out vec4 FragColor;
uniform float u_SpecularLight;
uniform vec4 u_Color;
uniform vec3 u_LightPosition;
uniform vec3 u_CameraPosition;
in vec3 normal;
in vec3 currentPosition;


void main()
{
    vec4 objectColor = u_Color;
    vec3 normalizedNormal = normalize(normal);

    vec3 lightDirection = normalize(u_LightPosition - currentPosition);
    vec3 viewDirection = normalize(u_CameraPosition - currentPosition);
    vec3 reflectionDirection = reflect(-lightDirection,normalizedNormal);
    float specularAmount = pow(max(dot(viewDirection,reflectionDirection),0.0f),2);
    float specular= specularAmount *u_SpecularLight;
    FragColor = objectColor *specular;
}