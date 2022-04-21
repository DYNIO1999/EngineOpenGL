#version 460 core


layout (points) in;
layout (triangle_strip, max_vertices =4) out;
uniform mat4 u_Projection;
uniform mat4 u_View;
uniform vec2 u_Size;
out vec2 uv;
void main(){
    vec4 position =gl_in[0].gl_Position;
    float width = u_Size.x;
    float height =u_Size.y;

    gl_Position =u_Projection*u_View*(position + vec4(-width, -height, 0.0f, 0.0f));
    uv = vec2(0.0f, 0.0f);
    EmitVertex();
    gl_Position = u_Projection*u_View*(position + vec4(width, -height, 0.0f, 0.0f));
    uv = vec2(1.0f, 0.0f);
    EmitVertex();
    gl_Position = u_Projection*u_View*(position + vec4(-width, height, 0.0f, 0.0f));
    uv = vec2(0.0f, 1.0f);
    EmitVertex();
    gl_Position = u_Projection*u_View*(position + vec4(width, height, 0.0f, 0.0f));
    uv = vec2(1.0f, 1.0f);
    EmitVertex();
    //gl_Position =u_Projection*u_View*(position + vec4(-width, -height, -0.5f, 0.0f));
    //uv = vec2(0.0f, 0.0f);
    //EmitVertex();
    //gl_Position = u_Projection*u_View*(position + vec4(width, -height, -0.5f, 0.0f));
    //uv = vec2(1.0f, 0.0f);
    //EmitVertex();
    //gl_Position = u_Projection*u_View*(position + vec4(-width, height, -0.5f, 0.0f));
    //uv = vec2(0.0f, 1.0f);
    //EmitVertex();
    //gl_Position = u_Projection*u_View*(position + vec4(width, height, -0.5f, 0.0f));
    //uv = vec2(1.0f, 1.0f);
    //EmitVertex();
    EndPrimitive();
}