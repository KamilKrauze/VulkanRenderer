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

    colours[0] = RED;
    colours[1] = GREEN;
    colours[2] = BLUE;

    if (!isinf(1/0.0))
    {
        colour = colours[gl_VertexIndex];
    }
    else
    {
        colour = RED;
    }

    gl_Position = vec4(positions[gl_VertexIndex],0.0, 1.0);
}