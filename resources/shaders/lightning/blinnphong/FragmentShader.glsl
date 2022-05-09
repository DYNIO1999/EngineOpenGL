#version 460
out vec4 FragColor;
uniform float u_SpecularLightStrength;
uniform float u_AmbientIntensity;

uniform vec3 u_Color;
uniform vec3 u_LightColor;
uniform vec3 u_LightPosition;
uniform vec3 u_CameraPosition;


in vec3 normal;
in vec3 currentPosition;

void main()
{
    vec3 ambient = u_AmbientIntensity *u_LightColor;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(u_LightPosition - currentPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * u_LightColor;


    vec3 viewDir = normalize(u_CameraPosition - currentPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    vec3 specular = vec3(0,0,0);
    if(diff!=0){
        vec3 halfway = normalize(viewDir + lightDir);
        float spec = pow(max(dot(norm, halfway), 0.0), 2);
        specular = u_SpecularLightStrength * spec * u_LightColor;
    }
    vec3 result = (ambient + diffuse + specular) * u_Color;
    FragColor = vec4(result, 1.0);
}