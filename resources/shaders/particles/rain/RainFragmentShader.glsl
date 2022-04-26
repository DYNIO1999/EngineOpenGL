#version 460
layout ( location = 0 ) out vec4 FragColor;

uniform vec4 u_Color;
in vec2 uv;
void main()
{
    vec4 col = u_Color;
    col.a = smoothstep(col.a, 0.0f, abs(uv.x - 0.5f) * 2.0f) * smoothstep(col.a, 0.0f, abs(uv.y - 0.5f) * 2.0f);
    FragColor = col;
}


