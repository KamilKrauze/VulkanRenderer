#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>
#include <optional>
#include <string>

#include "Core/Window.hpp"
#include "Core/KInstance.hpp"
#include "Core/GFXDevice.hpp"

#include "Utils/Macros.hpp"

#include <vulkan/vulkan.h>

class Application
{
public:
	explicit Application(WindowSpecification&& winSpec) : window(Window(std::move(winSpec))) {}
	~Application() = default;

public:
	void run()
	{
		window.create();
		initVulkan();
		mainLoop();
		cleanup();
	}
private:
	void initVulkan();
	void createLogicalDevice();

	void mainLoop();
	void cleanup();

private:
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	void createSwapChain();
	void createSwapChainImgViews();

	void createGraphicsPipeline();
	static std::vector<char> loadShader(const std::string& filename);
	VkShaderModule createShaderModule(const std::vector<char>& code);

	void createRenderPass();
	void createFramebuffers();

	void createCommandPool();
	void createCommandBuffers();
	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

	VkCommandBuffer beginSingleTimeCmds();
	void endSingleTimeCmds(VkCommandBuffer cmdBuffer);

	void createSyncObjects();

	void recreateSwapchain();
	void cleanupSwapchain();

	void drawFrame();

	void updateUniformBuffer(uint32_t currentImage);

	void createVertexBuffer();
	void createIndexBuffer();
	void createUniformBuffers();

	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void cpyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

	void createDescriptorSetLayout();
	void createDescriptorPool();
	void createDescriptorSets();

	void createTextureImage();
	void createImg(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits samples, VkFormat fmt, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags props, VkImage& img, VkDeviceMemory& imgMemory);
	void transitionImgLayout(VkImage img, VkFormat fmt, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);
	void copyBufferToImg(VkBuffer buffer, VkImage img, uint32_t width, uint32_t height);

	void createTextureImgView();
	VkImageView createImgView(VkImage img, VkFormat fmt, VkImageAspectFlags aspectFlags, uint32_t mipLevels);
	void createTextureSampler();

	void createDepthResources();
	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	VkFormat findDepthFormat();

	void generateMipmaps(VkImage img, VkFormat fmt, int32_t width, int32_t height, uint32_t mipLevels);

	VkSampleCountFlagBits getMaxUsableSampleCount();
	void createColourResources();

private:
	Window window;
	KInstance instance;

#if CHECK_BUILD_CONFIG
	VkDebugUtilsMessengerEXT debugMessenger;
#endif

	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice logicalDevice;
	VkQueue graphicsQueue;
	
	VkQueue presentQueue;
	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
	std::vector<VkImageView> swapChainImageViews;

	VkRenderPass renderPass;

	VkDescriptorSetLayout descriptorSetLayout;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;

	std::vector<VkFramebuffer> swapChainFramebuffers;

	VkCommandPool commandPool;

	std::vector<VkBuffer> uniformBuffers;
	std::vector<VkDeviceMemory> uniformBuffersMemory;
	std::vector<void*> uniformBuffersMapped;

	std::vector<VkCommandBuffer> commandBuffers;
	
	VkDescriptorPool descriptorPool;
	std::vector<VkDescriptorSet> descriptorSets;

	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;

	uint32_t mipLevels;
	VkImage textureImg;
	VkDeviceMemory textureImgMemory;
	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;

	VkImageView textureImgView;
	VkSampler textureSampler;

	VkImage depthImage;
	VkDeviceMemory depthImageMemory;
	VkImageView depthImgView;

	VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;
	VkImage colorImg;
	VkDeviceMemory colorImgMem;
	VkImageView colorImgView;
};

#endif //!APPLICATION_H