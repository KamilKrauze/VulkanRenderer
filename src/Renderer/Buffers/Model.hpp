#ifndef MODEL_HPP
#define MODEL_HPP

#include <string_view>

#include "Renderer/Buffers/Vertex.hpp"

class Model
{
public:
	Model() = default;

public:
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

private:
	VkBuffer vertexBuffer{};
	VkBuffer indexBuffer{};
	VkDeviceMemory vertexBufferMemory{};
	VkDeviceMemory indexBufferMemory{};
public:

	void load(std::string_view fp);

	VkBuffer& getVtxBuffer();
	VkBuffer& getIdxBuffer();

	VkDeviceMemory& getVtxMem();
	VkDeviceMemory& getIdxMem();

	void bindIdxBuffer(const VkCommandBuffer& cmdBuffer) const;
	void drawIdx(const VkCommandBuffer& cmdBuffer) const;

	void freeBuffers(VkDevice& logicalDevice);
};

#endif