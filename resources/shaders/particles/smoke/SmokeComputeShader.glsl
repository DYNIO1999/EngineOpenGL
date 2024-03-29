#version 460

layout( local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

layout(std430, binding=4) buffer _Pos1 {
    vec4 Position[];
};
layout(std430, binding=5) buffer _Vel1 {
    vec4 Velocity[];
};
uniform float PI = 3.14159265359;
uniform float u_DeltaTime;
uniform float MaxDist = 10.0;
void main() {

    uint idx = gl_GlobalInvocationID.x;
    vec3 pos = Position[idx].xyz;

    vec3 d =  vec3(0.0f, 0.0f,0.0f)- Position[idx].xyz;
    float dist = length(d);


    if( dist > MaxDist ) {
    Position[idx] = vec4(0,0,0,1);
    } else {
        vec3 vel = Velocity[idx].xyz;
        Position[idx].xyz= pos + vel *u_DeltaTime;
    }
}

