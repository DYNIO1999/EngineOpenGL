#version 460
out vec4 FragColor;
in vec3 normal;
in vec3 currentPosition;

uniform vec3 u_CameraPos;
uniform samplerCube u_Skybox;

void main()
{
    vec3 I = normalize(currentPosition - u_CameraPos);
    vec3 R = reflect(I, normalize(normal));
    FragColor = vec4(texture(u_Skybox, R).rgb, 1.0);
}