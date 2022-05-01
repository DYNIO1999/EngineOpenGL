#version 460 core
layout (points) in;
layout (triangle_strip, max_vertices =4) out;

uniform vec2 u_Size;
out vec2 uv;
void main(){
    vec4 position =gl_in[0].gl_Position;
    float width = u_Size.x;
    float height =u_Size.y;

    gl_Position =(position + vec4(-width, -height, 0.0f, 0.0f));
    uv = vec2(0.0f, 0.0f);
    EmitVertex();
    gl_Position = (position + vec4(width, -height, 0.0f, 0.0f));
    uv = vec2(1.0f, 0.0f);
    EmitVertex();
    gl_Position = (position + vec4(-width, height, 0.0f, 0.0f));
    uv = vec2(0.0f, 1.0f);
    EmitVertex();
    gl_Position = (position + vec4(width, height, 0.0f, 0.0f));
    uv = vec2(1.0f, 1.0f);
    EmitVertex();
    EndPrimitive();
}