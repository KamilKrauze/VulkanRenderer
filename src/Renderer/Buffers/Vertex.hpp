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

//const std::vector<Vertex> vertices = {
//    {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
//    {{0.5f, 0.5f},  {0.0f, 1.0f, 0.0f}},
//    {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
//};

const std::vector<Vertex> vertices = {
    {{-0.5f, -0.5f, 0.0f},    {1.0f, 0.0f, 0.0f}},
    {{0.5f, -0.5f, 0.0f},     {0.0f, 1.0f, 0.0f}},
    {{0.5f, 0.5f, 0.0f},      {0.0f, 0.0f, 1.0f}},
    {{-0.5f, 0.5f, 0.0f},     {1.0f, 1.0f, 1.0f}}
};

const std::vector<uint16_t> indices = {
    0, 1, 2, 2, 3, 0
};

//const std::vector<Vertex> vertices = {
//	// Face 0;
//		{{ -0.1f, 0.1f, -0.1f }, {1.0f, 0.0f, 0.0f}},
//		{{ -0.1f, -0.1f, -0.1f }, {0.0f, 1.0f, 0.0f}},
//		{{ 0.1f, -0.1f, -0.1f }, {0.0f, 0.0f, 1.0f}},
//
//		{{ 0.1f, -0.1f, -0.1f }, {1.0f, 0.0f, 0.0f}},
//		{{ 0.1f, 0.1f, -0.1f }, {0.0f, 1.0f, 0.0f}},
//		{{ -0.1f, 0.1f, -0.1f }, {0.0f, 0.0f, 1.0f}},
//
//		// Face 1
//		{{ 0.1f, -0.1f, -0.1f }, {1.0f, 0.0f, 0.0f}},
//		{{ 0.1f, -0.1f, 0.1f }, {0.0f, 1.0f, 0.0f}},
//		{{ 0.1f, 0.1f, -0.1f }, {0.0f, 0.0f, 1.0f}},
//
//		{{ 0.1f, -0.1f, 0.1f }, {1.0f, 0.0f, 0.0f}},
//		{{ 0.1f, 0.1f, 0.1f }, {0.0f, 1.0f, 0.0f}},
//		{{ 0.1f, 0.1f, -0.1f }, {0.0f, 0.0f, 1.0f}},
//
//		// Face 2
//		{{ 0.1f, -0.1f, 0.1f }, {1.0f, 0.0f, 0.0f}},
//		{{ -0.1f, -0.1f, 0.1f }, {0.0f, 1.0f, 0.0f}},
//		{{ 0.1f, 0.1f, 0.1f }, {0.0f, 0.0f, 1.0f}},
//
//		{{ -0.1f, -0.1f, 0.1f }, {1.0f, 0.0f, 0.0f}},
//		{{ -0.1f, 0.1f, 0.1f }, {0.0f, 1.0f, 0.0f}},
//		{{ 0.1f, 0.1f, 0.1f }, {0.0f, 0.0f, 1.0f}},
//
//		// Face 3
//		{{ -0.1f, -0.1f, 0.1f }, {1.0f, 0.0f, 0.0f}},
//		{{ -0.1f, -0.1f, -0.1f }, {0.0f, 1.0f, 0.0f}},
//		{{ -0.1f, 0.1f, 0.1f }, {0.0f, 0.0f, 1.0f}},
//
//		{{ -0.1f, -0.1f, -0.1f }, {1.0f, 0.0f, 0.0f}},
//		{{ -0.1f, 0.1f, -0.1f }, {0.0f, 1.0f, 0.0f}},
//		{{ -0.1f, 0.1f, 0.1f }, {0.0f, 0.0f, 1.0f}},
//
//		// Face 4
//		{{ -0.1f, -0.1f, 0.1f }, {1.0f, 0.0f, 0.0f}},
//		{{ 0.1f, -0.1f, 0.1f }, {0.0f, 1.0f, 0.0f}},
//		{{ 0.1f, -0.1f, -0.1f }, {0.0f, 0.0f, 1.0f}},
//
//		{{ 0.1f, -0.1f, -0.1f }, {1.0f, 0.0f, 0.0f}},
//		{{ -0.1f, -0.1f, -0.1f }, {0.0f, 1.0f, 0.0f}},
//		{{ -0.1f, -0.1f, 0.1f }, {0.0f, 0.0f, 1.0f}},
//
//		// Face 5
//		{{ -0.1f, 0.1f, -0.1f }, {1.0f, 0.0f, 0.0f}},
//		{{ 0.1f, 0.1f, -0.1f }, {0.0f, 1.0f, 0.0f}},
//		{{ 0.1f, 0.1f, 0.1f }, {0.0f, 0.0f, 1.0f}},
//
//		{{ 0.1f, 0.1f, 0.1f }, {1.0f, 0.0f, 0.0f}},
//		{{ -0.1f, 0.1f, 0.1f }, {0.0f, 1.0f, 0.0f}},
//		{{ -0.1f, 0.1f, -0.1f }, {0.0f, 0.0f, 1.0f}}
//};

#endif // !VERTEX_HPP