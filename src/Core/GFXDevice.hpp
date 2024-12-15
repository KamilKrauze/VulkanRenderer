#ifndef GFX_DEVICE_HPP
#define GFX_DEVICE_HPP

#include <optional>
#include <vector>

#include <vulkan/vulkan.h>

namespace GFXDevice
{
	namespace Details
	{
		struct QueueFamilyIndices
		{
			std::optional<uint32_t> graphicsFamily;
			std::optional<uint32_t> presentFamily;

			bool isComplete() { return graphicsFamily.has_value() && presentFamily.has_value(); }
		};

		struct SwapChainSupportDetails
		{
			VkSurfaceCapabilitiesKHR capabilities{};
			std::vector<VkSurfaceFormatKHR> formats;
			std::vector<VkPresentModeKHR> presentModes;
		};
	};

	GFXDevice::Details::QueueFamilyIndices findQueueFamilies(VkPhysicalDevice& device, VkSurfaceKHR surface);
	bool checkDeviceExtensionSupport(VkPhysicalDevice& device);
	Details::SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice& device, VkSurfaceKHR surface);
	
	bool isDeviceSuitable(VkPhysicalDevice& device, VkSurfaceKHR surface);
	int rateDeviceSuitability(VkPhysicalDevice& device);

	VkPhysicalDevice pickPhysicalDevice(VkInstance instance, VkSurfaceKHR surface);
};

#endif