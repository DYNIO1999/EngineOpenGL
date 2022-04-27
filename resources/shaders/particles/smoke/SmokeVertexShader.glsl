#version 460
in vec3 VertexInitVel; // Particle initial velocity
in float StartTime;    // Particle "birth" time

out float Transp;  // Transparency of the particle

uniform float u_Time;  // Animation time
uniform vec3 u_Gravity = vec3(0.0,-0.05,0.0);  // world coords
uniform float u_ParticleLifetime;  // Max particle lifetime

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    u_ParticleLifetime = 1.0f;
    // Assume the initial position is (0,0,0).
    vec3 pos = vec3(0.0);
    Transp = 0.0;

    // Particle dosen't exist until the start time
    if( u_Time > StartTime ) {
        float t = u_Time - StartTime;

        if( t < ParticleLifetime ) {
            pos = VertexInitVel * t + u_Gravity * t * t;
            Transp = 1.0 - t / ParticleLifetime;
        }
    }
    // Draw at the current position
    gl_Position = projection*view*model * vec4(pos, 1.0);
}