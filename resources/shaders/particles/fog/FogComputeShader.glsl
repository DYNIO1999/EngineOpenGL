#version 460

layout( local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

layout(std430, binding=0) buffer Pos {
    vec4 Position[];
};
layout(std430, binding=1) buffer Vel {
    vec4 Velocity[];
};
layout(std430, binding=2) buffer StartPos {
    vec4 StartingPos[];
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