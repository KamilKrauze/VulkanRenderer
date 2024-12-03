#version 450

layout (location=0) in vec3 fragColour;
layout (location=1) in vec2 fragTexCoord;
layout (location=2) in vec3 fragNormal;


layout(location=0) out vec4 outColour;
layout(binding = 1) uniform sampler2D texSampler;
void main()
{
    // outColour = vec4(fragColour, 1.0);
    outColour = vec4(texture(texSampler, fragTexCoord * 1).rgb, 1);
    // outColour = vec4(fragNormal, 1);
}