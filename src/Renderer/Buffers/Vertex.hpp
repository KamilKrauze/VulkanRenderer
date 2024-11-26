#ifndef VERTEX_HPP
#include <vector>
#include <array>

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>

struct Vertex
{
    glm::vec3 pos = { 0,0,0 };
    glm::vec3 colour = { 1,1,1 };
    glm::vec3 normal = { 0, 0, 1 };
    glm::vec2 texCoord = { 0, 0 };

    static VkVertexInputBindingDescription getBindDescription()
    {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        
        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 4> getAttributeDescriptions()
    {
        std::array<VkVertexInputAttributeDescription, 4> attributeDescriptions{};
        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, colour);

        attributeDescriptions[2].binding = 0;
        attributeDescriptions[2].location = 2;
        attributeDescriptions[2].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[2].offset = offsetof(Vertex, normal);

        attributeDescriptions[3].binding = 0;
        attributeDescriptions[3].location = 3;
        attributeDescriptions[3].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[3].offset = offsetof(Vertex, texCoord);

        return attributeDescriptions;
    }
};

struct UniformBufferObject
{
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};

#pragma region CUBE
//// Define the indices for the triangles that make up each face of the cube
//// Yes, IK this looks awful, watchu gonna do about it?
//std::vector<uint16_t> indices = {
//    // Top face
//    0, 1, 2,  0, 2, 3,
//
//    // Left face
//    5,6,7, 6,5,4,
//
//    // Bottom face
//    9,10,11, 10,9,8,
//
//    // Bottom face
//    14,13,12, 12,15,14,
//
//    // Front face
//    22,21,20, 20,21,23,
//
//    // Back face
//    16,17,18, 19,17,16
//};
//
//// Define the vertices for a unit cube centered at the origin
//std::vector<Vertex> vertices = {
//    // Top face
//    {{-0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 1.0f}, { -1.0f, -1.0f, 1.0f}}, // Vertex 0
//    {{ 0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 1.0f}, {  1.0f, -1.0f, 1.0f}}, // Vertex 1
//    {{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 1.0f}, {  1.0f,  1.0f, 1.0f}}, // Vertex 2
//    {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 1.0f}, { -1.0f,  1.0f, 1.0f}}, // Vertex 3
//
//    // Left face
//    {{-0.5f, -0.5f,  0.5f},  {1.0f, 0.0f, 0.0f}, {-1.0f, -1.0f,  1.0f}}, // Vertex 4
//    {{ 0.5f, -0.5f,  0.5f},  {1.0f, 1.0f, 0.0f}, { 1.0f, -1.0f,  1.0f}}, // Vertex 5
//    {{-0.5f, -0.5f, -0.5f},  {1.0f, 0.0f, 1.0f}, {-1.0f, -1.0f, -1.0f}}, // Vertex 6
//    {{ 0.5f, -0.5f, -0.5f},  {1.0f, 1.0f, 0.0f}, { 1.0f, -1.0f, -1.0f}}, // Vertex 7
//
//    // Right face
//    {{ 0.5f,  0.5f,  0.5f},  {1.0f, 0.0f, 0.0f}, { 1.0f,  1.0f,  1.0f}}, // Vertex 8
//    {{-0.5f,  0.5f,  0.5f},  {1.0f, 0.0f, 0.0f}, {-1.0f,  1.0f,  1.0f}}, // Vertex 9
//    {{ 0.5f,  0.5f,  -0.5f}, {1.0f, 0.0f, 0.0f}, { 1.0f,  1.0f,  -1.0f}}, // Vertex 10
//    {{-0.5f,  0.5f,  -0.5f}, {1.0f, 0.0f, 0.0f}, {-1.0f,  1.0f,  -1.0f}}, // Vertex 11
//
//    // Bottom face
//    {{-0.5f, -0.5f,  -0.5f}, {0.0f, 0.0f, 1.0f}, {-1.0f, -1.0f,  -1.0f}}, // Vertex 12
//    {{ 0.5f, -0.5f,  -0.5f}, {0.0f, 0.0f, 1.0f}, { 1.0f, -1.0f,  -1.0f}}, // Vertex 13
//    {{ 0.5f,  0.5f,  -0.5f}, {0.0f, 0.0f, 1.0f}, { 1.0f,  1.0f,  -1.0f}}, // Vertex 14
//    {{-0.5f,  0.5f,  -0.5f}, {0.0f, 0.0f, 1.0f}, {-1.0f,  1.0f,  -1.0f}}, // Vertex 15
//
//    // Back face
//    {{ -0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, { -1.0f,  1.0f, -1.0f}}, // Vertex 16
//    {{ -0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, { -1.0f, -1.0f,  1.0f}}, // Vertex 17
//    {{ -0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, { -1.0f,  1.0f,  1.0f}}, // Vertex 18
//    {{ -0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, { -1.0f, -1.0f, -1.0f}}, // Vertex 19
//
//    // Front face
//    {{ 0.5f,  0.5f, -0.5f},  {0.0f, 1.0f, 0.0f}, { 1.0f,  1.0f, -1.0f}}, // Vertex 20
//    {{ 0.5f, -0.5f,  0.5f},  {0.0f, 1.0f, 0.0f}, { 1.0f, -1.0f,  1.0f}}, // Vertex 21
//    {{ 0.5f,  0.5f,  0.5f},  {0.0f, 1.0f, 0.0f}, { 1.0f,  1.0f,  1.0f}}, // Vertex 22
//    {{ 0.5f, -0.5f, -0.5f},  {0.0f, 1.0f, 0.0f}, { 1.0f, -1.0f, -1.0f}}, // Vertex 23
//};
//
#pragma endregion

#pragma region Plane

std::vector<uint16_t> indices{
    0,1,2,
    2,3,0
};

std::vector<Vertex> vertices{
    {{ -0.5f,  0,  0.5f}, {1.0f, 0.0f, 0.0f}, {-1.0f, -1.0f,  -1.0f}, {1.0f, 0.0f}}, // Vertex 0
    {{  0.5f,  0,  0.5f}, {0.0f, 1.0f, 0.0f}, { 1.0f, -1.0f,  -1.0f}, {0.0f, 0.0f}}, // Vertex 1
    {{  0.5f,  0, -0.5f}, {0.0f, 0.0f, 1.0f}, { 1.0f,  1.0f,  -1.0f}, {0.0f, 1.0f}}, // Vertex 2
    {{ -0.5f,  0, -0.5f}, {1.0f, 1.0f, 1.0f}, {-1.0f,  1.0f,  -1.0f}, {1.0f, 1.0f}}, // Vertex 3
};

#pragma endregion



#endif // !VERTEX_HPP