#ifndef VERTEX_HPP
#include <vector>
#include <array>

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>

struct Vertex
{
    glm::vec3 pos;
    glm::vec3 colour;

    static VkVertexInputBindingDescription getBindDescription()
    {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        
        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions()
    {
        std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, colour);

        return attributeDescriptions;
    }
};

struct UniformBufferObject
{
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};

//const std::vector<Vertex> vertices = {
//    {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
//    {{0.5f, 0.5f},  {0.0f, 1.0f, 0.0f}},
//    {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
//};

//const std::vector<Vertex> vertices = {
//    {{-0.5f, -0.5f, 0.0f},    {1.0f, 0.0f, 0.0f}},
//    {{0.5f, -0.5f, 0.0f},     {0.0f, 1.0f, 0.0f}},
//    {{0.5f, 0.5f, 0.0f},      {0.0f, 0.0f, 1.0f}},
//    {{-0.5f, 0.5f, 0.0f},     {1.0f, 1.0f, 1.0f}}
//};

//const std::vector<uint16_t> indices = {
//    0, 1, 2, 2, 3, 0
//};

// Define the indices for the triangles that make up each face of the cube
std::vector<uint16_t> indices = {
    // Front face (counterclockwise)
    0, 1, 2,  0, 2, 3,

    // Back face (counterclockwise)
    5, 4, 7,  5, 7, 6,

    // Left face (counterclockwise)
    4, 0, 3,  4, 3, 7,

    // Right face (counterclockwise)
    1, 5, 6,  1, 6, 2,

    // Top face (counterclockwise)
    4, 5, 1,  4, 1, 0,

    // Bottom face (counterclockwise)
    3, 2, 6,  3, 6, 7
};

// Define the vertices for a unit cube centered at the origin
std::vector<Vertex> vertices = {
    // Front face
    {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}}, // Vertex 0
    {{ 0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}}, // Vertex 1
    {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}}, // Vertex 2
    {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}}, // Vertex 3

    // Back face
    {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}}, // Vertex 4
    {{ 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 1.0f}}, // Vertex 5
    {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}}, // Vertex 6
    {{-0.5f,  0.5f, -0.5f}, {0.5f, 0.5f, 0.5f}}  // Vertex 7
};

#endif // !VERTEX_HPP