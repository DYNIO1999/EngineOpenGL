#version 400

layout( quads ) in;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float sin;
out vec2 texTestCord;

void BernsteinPolynomial( out float[4] b, float t )
{
    float t1 = (1.0 - t);
    float t12 = t1 * t1;

    b[0] = t12 * t1;
    b[1] = 3.0 * t12 * t;
    b[2] = 3.0 * t1 * t * t;
    b[3] = t * t * t;
}

void main()
{
    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;
    texTestCord  = vec2(v,u);
    vec4 p00 = gl_in[0].gl_Position;
    vec4 p01 = gl_in[1].gl_Position;
    vec4 p02 = gl_in[2].gl_Position;
    vec4 p03 = gl_in[3].gl_Position;
    vec4 p10 = gl_in[4].gl_Position;
    vec4 p11 = gl_in[5].gl_Position;
    vec4 p12 = gl_in[6].gl_Position;
    vec4 p13 = gl_in[7].gl_Position;
    vec4 p20 = gl_in[8].gl_Position;
    vec4 p21 = gl_in[9].gl_Position;
    vec4 p22 = gl_in[10].gl_Position;
    vec4 p23 = gl_in[11].gl_Position;
    vec4 p30 = gl_in[12].gl_Position;
    vec4 p31 = gl_in[13].gl_Position;
    vec4 p32 = gl_in[14].gl_Position;
    vec4 p33 = gl_in[15].gl_Position;

    float bu[4], bv[4];

    BernsteinPolynomial(bu,u);
    BernsteinPolynomial(bv,v);

    vec4 pos  =  vec4(p00)*bu[0]*bv[0] +
    vec4(p01.x,p01.y*sin,p01.z,p01.w)*bu[0]*bv[1] +
    vec4(p02.x,p02.y*sin,p02.z,p02.w)*bu[0]*bv[2] +
    vec4(p03)*bu[0]*bv[3] +
    vec4(p10)*bu[1]*bv[0] +
    vec4(p11.x,p11.y*sin,p11.z,p11.w)*bu[1]*bv[1] +
    vec4(p12.x,p12.y*sin,p12.z,p12.w)*bu[1]*bv[2] +
    vec4(p13)*bu[1]*bv[3] +
    vec4(p20)*bu[2]*bv[0] +
    vec4(p21.x,p21.y*sin,p21.z,p21.w)*bu[2]*bv[1] +
    vec4(p22.x,p22.y*sin,p22.z,p22.w)*bu[2]*bv[2] +
    vec4(p23)*bu[2]*bv[3] +
    vec4(p30)*bu[3]*bv[0] +
    vec4(p31.x,p31.y*sin,p31.z,p31.w)*bu[3]*bv[1] +
    vec4(p32.x,p32.y*sin,p32.z,p32.w)*bu[3]*bv[2] +
    vec4(p33)*bu[3]*bv[3];

    gl_Position =  projection* view* model * pos;
}