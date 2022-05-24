#version 460
out vec4 FragColor;
in vec3 normal;
in vec3 currentPosition;

uniform vec3 u_CameraPos;
uniform samplerCube u_Skybox;
/*
The refractive index determines the amount light distorts/bends in a material where each material has its own refractive index.
A list of the most common refractive indices are given in the following table:
Material 	Refractive index
Air 	1.00
Water 	1.33
Ice 	1.309
Glass 	1.52
Diamond 	2.42
*/
void main()
{
    float ratio = 1.00 / 1.52;
    vec3 I = normalize(currentPosition - u_CameraPos);
    vec3 R = refract(I, normalize(normal), ratio);
    FragColor = vec4(texture(u_Skybox, R).rgb, 1.0);
}