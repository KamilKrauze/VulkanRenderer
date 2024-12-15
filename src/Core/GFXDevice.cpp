#include "Core/GFXDevice.hpp"
#include "Utils/Logger.hpp"

#include <stdexcept>
#include <map>
#include <iostream>
#include <set>
#include <Utils/Extensions.hpp>


GFXDevice::Details::QueueFamilyIndices GFXDevice::findQueueFamilies(VkPhysicalDevice& device, VkSurfaceKHR surface)
{
	GFXDevice::Details::QueueFamilyIndices indices;
	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	int i = 0;
	for (const auto& family : queueFamilies)
	{
		if (family.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			indices.graphicsFamily = i;

		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

		if (presentSupport)
		{
			indices.presentFamily = i;
		}

		if (indices.isComplete())
		{
			break;
		}

		i++;
	}

	return indices;
}

bool GFXDevice::checkDeviceExtensionSupport(VkPhysicalDevice& device)
{

	uint32_t extensionCount;
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> availableExts(extensionCount);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExts.data());

	std::set<std::string> requiredExts(GFXExt::deviceExtensions.begin(), GFXExt::deviceExtensions.end());

	for (const auto& ext : availableExts)
		requiredExts.erase(ext.extensionName);

	return requiredExts.empty();
}

GFXDevice::Details::SwapChainSupportDetails GFXDevice::querySwapChainSupport(VkPhysicalDevice& device, VkSurfaceKHR surface)
{
	GFXDevice::Details::SwapChainSupportDetails details;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

	uint32_t formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

	if (formatCount != 0)
	{
		details.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
	}

	uint32_t presentModeCount = 0;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

	if (presentModeCount != 0)
	{
		details.presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
	}

	return details;
}

bool GFXDevice::isDeviceSuitable(VkPhysicalDevice& device, VkSurfaceKHR surface)
{
	GFXDevice::Details::QueueFamilyIndices indices = findQueueFamilies(device, surface);

	bool extensionsSupported = checkDeviceExtensionSupport(device);

	bool swapChainAdequate = false;
	if (extensionsSupported)
	{
		GFXDevice::Details::SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device, surface);
		swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
	}

	return indices.isComplete() && extensionsSupported && swapChainAdequate;
}

int GFXDevice::rateDeviceSuitability(VkPhysicalDevice& device)
{
	VkPhysicalDeviceProperties deviceProps;
	vkGetPhysicalDeviceProperties(device, &deviceProps);

	VkPhysicalDeviceFeatures deviceFeatures;
	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

	int score = 0;

	// Discrete GPUs have a significant performance advantage
	if (deviceProps.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		score += 1000;

	score += deviceProps.limits.maxImageDimension2D;

	if (!deviceFeatures.geometryShader)
		score = 0;

	return score;
}

VkPhysicalDevice GFXDevice::pickPhysicalDevice(VkInstance instance, VkSurfaceKHR surface)
{
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

	constexpr const char* ERROR_MSG = "Failed to find a suitable GPU!";
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
	if (deviceCount == 0)
		throw std::runtime_error("Failed to find any GPU with Vulkan support!");

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

	for (auto& device : devices)
	{
		if (isDeviceSuitable(device, surface))
		{
			physicalDevice = device;
			break;
		}
	}

	if (physicalDevice == VK_NULL_HANDLE)
		throw std::runtime_error(ERROR_MSG);

	std::cout << "GPU Name|Suitability Score\n";
	std::multimap<int, VkPhysicalDevice> candidates;
	for (auto& device : devices)
	{
		int score = rateDeviceSuitability(device);
		VkPhysicalDeviceProperties deviceProps;
		vkGetPhysicalDeviceProperties(device, &deviceProps);
		std::cout << deviceProps.deviceName << "|" << score << "\n";

		candidates.insert(std::make_pair(score, device));
	}

	if (candidates.rbegin()->first > 0)
		physicalDevice = candidates.rbegin()->second;
	else
		throw std::runtime_error(ERROR_MSG);

	LOG_SUCCESS("Successfully selected physical GPU with Vulkan support!");
	return physicalDevice;
}