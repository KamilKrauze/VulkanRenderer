#version 450

layout (location=0) in vec3 fragColour;
layout (location=1) in vec2 fragTexCoord;

layout(location=0) out vec4 outColour;
layout(binding = 1) uniform sampler2D texSampler;
void main()
{
    // outColour = vec4(fragColour, 1.0);
    outColour = vec4(fragColour*texture(texSampler, fragTexCoord * 1).rgb, 1);
}