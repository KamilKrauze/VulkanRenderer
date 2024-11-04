#version 450

#include "colour.glsl"

vec2 positions[3];

vec3 colours[3];
layout(location=1) out vec3 colour;

void main()
{
    positions[0] = vec2(0.0, -0.5);
    positions[1] = vec2(0.5, 0.5);
    positions[2] = vec2(-0.5, 0.5);

    colours[0] = vec3(1,0,0);
    colours[1] = red() + green();
    colours[2] = vec3(0,0,1);

    colour = colours[gl_VertexIndex];

    gl_Position = vec4(positions[gl_VertexIndex],0.0, 1.0);
}