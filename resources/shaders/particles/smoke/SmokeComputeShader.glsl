#version 460

layout( local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

layout(std430, binding=0) buffer Pos {
    vec4 Position[];
};
layout(std430, binding=1) buffer Vel {
    vec4 Velocity[];
};
layout(std430, binding=2) buffer Age {
    float ParticleLifeTime[];
};
uniform float PI = 3.14159265359;
uniform float DeltaTime;
uniform float maxLifeTime =1.0f;
uniform mat3 EmitterBasis;
uniform float MaxDist = 10.0;


//vec3 randomInitialVelocity() {
//
//    float x = mix(0.0f, 1.0f, 0.1);
//    float y = mix(0.0f, 1.0f, 0.1);
//    float z = 0.0f;
//    vec3 v = vec3(x,y,z);
//    return normalize(v);
//}
//void main() {
//
//    uint idx = gl_GlobalInvocationID.x;
//    // Velocity[idx].xyz = vec3(0.2f,1.0f,0.0f);
//    //if(ParticleLifeTime[idx]<=0){
//    //    Velocity[idx] = randomInitialVelocity();
//    //}
//    //ParticleLifeTime[idx] = ParticleLifeTime[idx]+DeltaTime;
//    Velocity[idx].xyz = Velocity[idx].xyz+vec3(5.0f,10.0f,0.0f);
//    Position[idx].xyz= Position[idx].xyz + (Velocity[idx].xyz);
//}

void main() {

    uint idx = gl_GlobalInvocationID.x;
    vec3 pos = Position[idx].xyz;
    // Velocity[idx].xyz = vec3(0.2f,1.0f,0.0f);

    vec3 d =  vec3(0.0f, 0.0f,0.0f)- Position[idx].xyz;
    float dist = length(d);

    if(ParticleLifeTime[idx]>maxLifeTime){

    }

    if( dist > MaxDist ) {
    Position[idx] = vec4(0,0,0,1);
    } else {
        ParticleLifeTime[idx] = ParticleLifeTime[idx]+DeltaTime;
        vec3 vel = Velocity[idx].xyz;
        Position[idx].xyz= pos + vel *DeltaTime;
    }
}

