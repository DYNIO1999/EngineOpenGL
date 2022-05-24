#version 460
out vec4 FragColor;
in vec2 v_TextCoord;
uniform sampler2D u_Texture;
uniform int u_TreshHolding;
void main()
{
    vec4 color = texture(u_Texture,v_TextCoord);


    if(u_TreshHolding == 1){
        float grey = color.r+color.g+color.b;
        grey /= 3;
        if(grey < 0.7)
        grey = 0.0f;
    else
        grey = 1.0f;
        color = vec4(grey,grey,grey, color.a);
    }
    if(u_TreshHolding == 2){
        float threshold = 0.5f;
        if(color.r < threshold)
        color.r = 0.0f;
    else
        color.r = 1.0f;
        if(color.g < threshold)
        color.g = 0.0f;
    else
        color.g = 1.0f;
        if(color.b < threshold)
        color.b = 0.0f;
    else
        color.b = 1.0f;
    }
    FragColor = color;
}
