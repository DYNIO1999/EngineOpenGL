#version 460

layout( local_size_x = 1000 ) in;

uniform vec3 u_Gravity = vec3(0.0,-1, 0.0);
uniform float deltaTime = 1;
uniform float MaxDist = 20;


layout(std430, binding=3) buffer Pos {
    vec4 Position[];
};
layout(std430, binding=4) buffer Vel {
    vec4 Velocity[];
};
layout(std430, binding=5) buffer StartPos {
    vec4 StartingPos[];
};


void main() {
    uint idx = gl_GlobalInvocationID.x;

    vec3 pos = Position[idx].xyz;
    pos.y=pos.y +u_Gravity.y *deltaTime;

    pos.y = mod(pos.y, 100.0f)-50;
    Position[idx].xyz = pos;

}