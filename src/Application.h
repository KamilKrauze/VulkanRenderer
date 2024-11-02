#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>
#include <string>

#include "Core/Window.hpp"
#include "Renderer/GfxDevice.hpp"

#include <vulkan/vulkan.h>

class Application
{
public:
	Application() = default;
	~Application() = default;

public:
	void run()
	{

		window = new Window({800, 600, "Vulkan"});
		initVulkan();
		mainLoop();
		cleanup();
	}
private:

	void initVulkan();
	void createInstance();

	void mainLoop();
	void cleanup();

private:
	std::vector<const char*> getRequiredExtensions();

	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	void createSwapChain();
	void createImageViews();

	void createGraphicsPipeline();
	static std::vector<char> loadShader(const std::string& filename);
	VkShaderModule createShaderModule(const std::vector<char>& code);

	void createRenderPass();
	void createFramebuffers();

	void createCommandPool();
	void createCommandBuffers();
	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

	void createSyncObjects();

	void recreateSwapchain();
	void cleanupSwapchain();

	void drawFrame();

private:
	Window* window;
	VkInstance instance;
	VkDebugUtilsMessengerEXT debugMessenger;

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
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;

	std::vector<VkFramebuffer> swapChainFramebuffers;

	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;

	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;

};

#endif //!APPLICATION_H