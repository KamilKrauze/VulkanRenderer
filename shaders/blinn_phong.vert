#version 450

layout(set=0, binding=0) uniform UniformBufferObject
{
    mat4 model;
    mat4 view;
    mat4 proj;
} mvp;

layout (location=0) in vec3 v_Position;
layout (location=1) in vec3 v_Colour;
layout (location=2) in vec3 v_Normal;
layout (location=3) in vec2 v_texCoord;

layout (location = 0) out vec3 fragColour;
layout (location = 1) out vec2 fragTexCoord;

void main()
{
    gl_Position = mvp.proj * mvp.view * mvp.model * vec4(v_Position, 1.0f);
    fragColour = v_Colour;
    fragTexCoord = v_texCoord;
}