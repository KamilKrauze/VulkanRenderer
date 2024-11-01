#ifndef DEBUG_MSG_HPP
#define DEBUG_MSG_HPP

#include "Utils/logger.hpp"

#include <sstream>
#include <vector>

#include <vulkan/vulkan.h>

namespace Debug
{

const std::vector<const char*> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
};

#if defined(NDEBUG)
	constexpr bool enableValidationLayers = false;
#elif defined(DEBUG) && defined(USE_VALIDATION_LAYERS)

	constexpr bool enableValidationLayers = true;

#else 
	constexpr bool enableValidationLayers = false;
#endif

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
	{

		std::stringstream ss;
		ss << "Validation layer: " << pCallbackData->pMessage << "\n";

		switch (messageSeverity)
		{
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
			LOG_VERBOSE(ss.str().c_str());
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
			LOG_INFO(ss.str().c_str());
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
			LOG_WARNING(ss.str().c_str());
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
			LOG_ERROR(ss.str().c_str());
			break;
		}

		return VK_FALSE;
	}

	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
	{
		createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		createInfo.pfnUserCallback = debugCallback;
		createInfo.pUserData = nullptr; // Optional
	}

	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger)
	{
		auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
		if (func != nullptr) {
			return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
		}
		else {
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator)
	{
		auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
		if (func != nullptr) {
			func(instance, debugMessenger, pAllocator);
		}
	}

	void setupDebugMessenger(VkInstance& instance, VkDebugUtilsMessengerEXT& debugMessenger)
	{
		if (!enableValidationLayers)
			return;

		VkDebugUtilsMessengerCreateInfoEXT createInfo{};
		populateDebugMessengerCreateInfo(createInfo);

		if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS)
			throw std::runtime_error("Failed to setup debug messenger!");

		LOG_SUCCESS("Debug messenger setup!");
	}

	bool checkValidationLayerSupport()
	{
		uint32_t layerCount = 0;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		for (const char* name : Debug::validationLayers)
		{
			bool layerFound = false;

			for (const auto& properties : availableLayers)
			{
				if (strcmp(name, properties.layerName) == 0) {
					layerFound = true;
					break;
				}
			}
			if (!layerFound)
				return false;
		}

		return true;
	}
}

#endif // !DEBUG_MSG_HPP