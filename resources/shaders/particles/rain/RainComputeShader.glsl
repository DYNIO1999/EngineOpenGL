#version 460

layout(local_size_x = 128, local_size_y = 1, local_size_z = 1) in;

layout(std430, binding=0) buffer Pos {
    vec4 Position[];
};

uniform vec3 u_Gravity = vec3(0.0,-1, 0.0);
uniform float u_DeltaTime;
void main() {
    uint idx = gl_GlobalInvocationID.x;

    vec3 pos = Position[idx].xyz;
    pos.y=pos.y +u_Gravity.y *u_DeltaTime;

    pos.y = mod(pos.y, 100.0f)-50;
    Position[idx].xyz = pos;

}