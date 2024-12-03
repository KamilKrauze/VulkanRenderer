#include "Model.hpp"
#include "Utils/logger.hpp"

#include <unordered_map>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyObj/tiny_obj_loader.h>

void Model::load(std::string_view fp)
{
	{
		std::string msg = "Loading: " + std::string(fp);
		LOG_VERBOSE(msg.c_str());
	}
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn, err;

	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, fp.data()))
	{
		if (!err.empty())
		{
			throw std::runtime_error(err);
		}
		LOG_WARNING(warn.c_str());
	}
	else
	{
		std::string msg = "Successfully loaded: " + std::string(fp);
		LOG_INFO(msg.c_str());
	}

	std::unordered_map<Vertex, uint32_t> uniqueVertices{};

	for (const auto& shape : shapes)
	{
		for (const auto& index : shape.mesh.indices)
		{
			Vertex vert{};
			vert.pos = {
				attrib.vertices[3 * index.vertex_index + 0],
				attrib.vertices[3 * index.vertex_index + 1],
				attrib.vertices[3 * index.vertex_index + 2]
			};

			vert.texCoord = {
				attrib.texcoords[2 * index.texcoord_index + 0],
				1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
			};

			vert.normal = {
				attrib.normals[3 * index.normal_index + 0],
				attrib.normals[3 * index.normal_index + 1],
				attrib.normals[3 * index.normal_index + 2],
			};

			vert.colour = {1,1,1};

			if (uniqueVertices.count(vert) == 0)
			{
				uniqueVertices[vert] = static_cast<uint32_t>(vertices.size());
				vertices.push_back(vert);
			}

			indices.push_back(uniqueVertices[vert]);
		}
	}
}

VkBuffer& Model::getVtxBuffer()
{
	return vertexBuffer;
}

VkBuffer& Model::getIdxBuffer()
{
	return indexBuffer;
}

VkDeviceMemory& Model::getVtxMem()
{
	return vertexBufferMemory;
}

VkDeviceMemory& Model::getIdxMem()
{
	return indexBufferMemory;
}

void Model::bindIdxBuffer(const VkCommandBuffer& cmdBuffer) const
{
	vkCmdBindIndexBuffer(cmdBuffer, indexBuffer, 0, VK_INDEX_TYPE_UINT32);
}

void Model::drawIdx(const VkCommandBuffer& cmdBuffer) const
{
	vkCmdDrawIndexed(cmdBuffer, static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);
}

void Model::freeBuffers(VkDevice& logicalDevice)
{
	vkDestroyBuffer(logicalDevice, indexBuffer, nullptr);
	vkFreeMemory(logicalDevice, indexBufferMemory, nullptr);

	vkDestroyBuffer(logicalDevice, vertexBuffer, nullptr);
	vkFreeMemory(logicalDevice, vertexBufferMemory, nullptr);
}
