#ifndef GFX_DEVICE_HPP
#define GFX_DEVICE_HPP

#include "Utils/logger.hpp"
#include "Renderer/DebugMsg.hpp"

#include <set>
#include <map>
#include <cstdint>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <optional>

#include <vulkan/vulkan.h>

namespace GfxDevice
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
			VkSurfaceCapabilitiesKHR capabilities;
			std::vector<VkSurfaceFormatKHR> formats;
			std::vector<VkPresentModeKHR> presentModes;
		};
	}

	const static std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	// Logic to find queue family indices to populate struct with
	inline Details::QueueFamilyIndices findQueueFamilies(const VkPhysicalDevice& device, const VkSurfaceKHR& surface)
	{
		Details::QueueFamilyIndices indices;
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
				indices.presentFamily = i;

			if (indices.isComplete())
				break;

			i++;
		}

		return indices;
	}

	inline bool checkDeviceExtensionSupport(VkPhysicalDevice device)
	{

		uint32_t extensionCount;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> availableExts(extensionCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExts.data());

		std::set<std::string> requiredExts(deviceExtensions.begin(), deviceExtensions.end());

		for (const auto& ext : availableExts)
			requiredExts.erase(ext.extensionName);

		return requiredExts.empty();
	}

	inline Details::SwapChainSupportDetails querySwapChainSupport(const VkPhysicalDevice& device, const VkSurfaceKHR& surface)
	{
		Details::SwapChainSupportDetails details;
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

	inline bool isDeviceSuitable(const VkPhysicalDevice& device, const VkSurfaceKHR& surface)
	{
		Details::QueueFamilyIndices indices = findQueueFamilies(device, surface);

		bool extensionsSupported = checkDeviceExtensionSupport(device);

		bool swapChainAdequate = false;
		if (extensionsSupported)
		{
			Details::SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device, surface);
			swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
		}

		return indices.isComplete() && extensionsSupported && swapChainAdequate;

#pragma region Old code

		//VkPhysicalDeviceProperties deviceProps;
		//vkGetPhysicalDeviceProperties(device, &deviceProps);

		//VkPhysicalDeviceFeatures deviceFeatures;
		//vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

		//return deviceProps.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && deviceFeatures.geometryShader;
#pragma endregion

	}

	inline int rateDeviceSuitability(const VkPhysicalDevice& device)
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

	inline VkPhysicalDevice pickPhysicalDevice(VkInstance& instance, const VkSurfaceKHR& surface)
	{
		VkPhysicalDevice physicalDevice;

		constexpr const char* ERROR_MSG = "Failed to find a suitable GPU!";
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
		if (deviceCount == 0)
			throw std::runtime_error("Failed to find any GPU with Vulkan support!");

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

		for (const auto& device : devices)
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
		for (const auto& device : devices)
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

	inline VkDevice createLogicalDevice(const VkPhysicalDevice& physicalDevice, const VkSurfaceKHR& surface, VkQueue& graphicsQueue, VkQueue& presentQueue)
	{
		VkDevice logicalDevice;
		Details::QueueFamilyIndices indices = findQueueFamilies(physicalDevice, surface);

		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

		float queuePriority = 1.0f;
		for (uint32_t queueFamily : uniqueQueueFamilies)
		{
			VkDeviceQueueCreateInfo queueCreateInfo{};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queueFamily;
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &queuePriority;
			queueCreateInfos.push_back(queueCreateInfo);
		}

		VkPhysicalDeviceFeatures deviceFeatures{};
		VkDeviceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());;
		createInfo.pQueueCreateInfos = queueCreateInfos.data();
		createInfo.pEnabledFeatures = &deviceFeatures;
		createInfo.enabledExtensionCount = static_cast<uint32_t>(GfxDevice::deviceExtensions.size());
		createInfo.ppEnabledExtensionNames = GfxDevice::deviceExtensions.data();

		if (Debug::enableValidationLayers)
		{
			createInfo.enabledLayerCount = static_cast<uint32_t>(Debug::validationLayers.size());
			createInfo.ppEnabledLayerNames = Debug::validationLayers.data();
		}
		else {
			createInfo.enabledLayerCount = 0;
		}

		if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &logicalDevice) != VK_SUCCESS)
			throw std::runtime_error("Failed to create logical device!");

		vkGetDeviceQueue(logicalDevice, indices.graphicsFamily.value(), 0, &graphicsQueue);
		vkGetDeviceQueue(logicalDevice, indices.presentFamily.value(), 0, &presentQueue);

		LOG_SUCCESS("Logical device successfully created!");
		return logicalDevice;
	}
};

#endif