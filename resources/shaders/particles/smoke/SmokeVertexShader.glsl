#version 460
in vec3 aPos;
out float Transp;

uniform mat4 u_MVP;
uniform float Time;
uniform float ParticleLifetime;
void main()
{
    float t = Time;
    if((aPos.x >= 0.0f && aPos.x <= 0.2f) && (aPos.z >= 0.0f && aPos.z <= 0.2f)){
        Transp =1.0f;
    }else {
        Transp= 1.0 - t/ParticleLifetime;
    }

    gl_Position =u_MVP* vec4(aPos,1);
}



