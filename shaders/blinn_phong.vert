#version 450

layout(binding=0) uniform UniformBufferObject
{
    mat4 model;
    mat4 view;
    mat4 proj;
} mvp;

layout(location=0) in vec3 v_Position;
layout(location=1) in vec3 v_Colour;
layout(location=2) in vec3 v_Normal;

layout (location = 0) out vec3 fragColour;

void main()
{
    gl_Position = mvp.proj * mvp.view * mvp.model * vec4(v_Position, 1.0f);
    fragColour = v_Position;
}