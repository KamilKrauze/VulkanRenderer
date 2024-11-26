#version 450

layout (location=0) in vec3 fragColour;
layout (location=1) in vec2 fragTexCoord;

layout(location=0) out vec4 outColour;
layout(binding = 1) uniform sampler2D texSampler;

vec2 res = vec2(512,512);
vec2 texelSize = vec2(1/res.x, 1/res.y);

// Gaussian blur kernel weights
float gaussian(float x, float sigma) {
    return exp(-0.5 * (x * x) / (sigma * sigma)) / (sqrt(6.28318530718) * sigma);
}

vec4 applyGaussianBlur(sampler2D tex, vec2 uv, float sigma) {
    int kernelRadius = int(ceil(3.0 * sigma));
    vec4 color = vec4(0.0);
    float sum = 0.0;

    // Horizontal pass
    for (int x = -kernelRadius; x <= kernelRadius; ++x) {
        float weight = gaussian(float(x), sigma);
        vec2 offset = vec2(float(x) * texelSize.x, 0.0);
        color += texture(tex, uv + offset) * weight;
        sum += weight;
    }
    color /= sum;

    vec4 verticalBlur = vec4(0.0);
    sum = 0.0;
    // Vertical pass
    for (int y = -kernelRadius; y <= kernelRadius; ++y) {
        float weight = gaussian(float(y), sigma);
        vec2 offset = vec2(0.0, float(y) * texelSize.y);
        verticalBlur += texture(tex, uv + offset) * weight;
        sum += weight;
    }
    verticalBlur /= sum;

    return verticalBlur;
}

void main()
{
// Compute sigma1 and sigma2 dynamically based on texture resolution
    float maxDimension = max(res.x, res.y);
    float sigma1 = maxDimension * 0.005; // Example: small blur
    float sigma2 = maxDimension * 0.01; // Example: larger blur

    // Apply Gaussian blurs with the computed sigmas
    vec4 blurred1 = applyGaussianBlur(texSampler, fragTexCoord, sigma1);
    vec4 blurred2 = applyGaussianBlur(texSampler, fragTexCoord, sigma2);

    // Compute the difference of Gaussians
    vec4 dog = blurred1 - blurred2;

    // Estimate gradients using central differences
    float dX = (texture(texSampler, fragTexCoord + vec2(texelSize.x, 0.0)).r -
                texture(texSampler, fragTexCoord - vec2(texelSize.x, 0.0)).r) * 0.5;
    float dY = (texture(texSampler, fragTexCoord + vec2(0.0, texelSize.y)).r -
                texture(texSampler, fragTexCoord - vec2(0.0, texelSize.y)).r) * 0.5;

    // Normalize the gradient to get the tangent direction
    vec2 tangent = normalize(vec2(dX, dY));

    // // Map the tangent to [0,1] for visualization
    // vec2 tangentNormalized = tangent * 0.5 + 0.5;

    // Compute gradient magnitude (edge strength)
    float gradientMagnitude = length(vec2(dX, dY));

    float edgeThreshold = 0.015;
    // Apply edge threshold to isolate edges
    float edge = gradientMagnitude > edgeThreshold ? 1.0 : 0.0;

    // outColour = vec4(fragColour, 1.0);
    outColour = vec4(vec3(edge), 1.0);
}