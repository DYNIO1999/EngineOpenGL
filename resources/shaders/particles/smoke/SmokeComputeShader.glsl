#version 460

layout( local_size_x = 1000, local_size_y = 1, local_size_z = 1) in;

layout(std430) buffer Pos {
    vec4 Position[];
};
layout(std430) buffer Vel {
    vec4 Velocity[];
};
layout(std430) buffer Age {
    float ParticleLifeTime[];
};
uniform mat3 EmitterBasis;
uniform float PI = 3.14159265359;
uniform float DeltaTime;

vec3 randomInitialVelocity() {

    float theta = mix(0.0, PI / 1.5, 10.0f);
    float phi = mix(0.0, 2.0 * PI, 10.0f);
    float velocity = mix(0.1, 0.2, 10.0f);
    vec3 v = vec3(sin(theta) * cos(phi), cos(theta), sin(theta) * sin(phi));
    return normalize(EmitterBasis * v) * velocity;
}
void main() {

    uint idx = gl_GlobalInvocationID.x;
    vec3 pos = Position[idx].xyz;

    if(ParticleLifeTime[idx]<=0){
        Velocity[idx].xyz = randomInitialVelocity();
    }
    ParticleLifeTime[idx] = ParticleLifeTime[idx]+DeltaTime;
    Position[idx].xyz= pos + (Velocity[idx].xyz* DeltaTime);
}
