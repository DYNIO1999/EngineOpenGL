#version 460

in float Transp;
//uniform sampler2D ParticleTex;
out vec4 FragColor;

void main()
{
    //texture(ParticleTex, gl_PointCoord)
    FragColor = vec4(0.5f,0.5f,0.5f,1.0f);
    FragColor.a *= Transp;
}