#include "KInstance.hpp"

#include <Core/DebugMessenger.hpp>
#include <Utils/Extensions.hpp>
#include <Utils/Macros.hpp>

void KInstance::create(VkApplicationInfo& appInfo)
{
#if CHECK_BUILD_CONFIG
	if (!Debug::checkValidationLayerSupport())
		throw std::runtime_error("Validation layers requested, but not available!");
	else
		LOG_INFO("Running Vulkan application with validation layers.\n");
#endif

	auto extensions = GFXExt::getRequiredExtensions();

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	createInfo.ppEnabledExtensionNames = extensions.data();

#if CHECK_BUILD_CONFIG
	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};

	createInfo.enabledLayerCount = static_cast<uint32_t>(Debug::validationLayers.size());
	createInfo.ppEnabledLayerNames = Debug::validationLayers.data();

	Debug::populateDebugMessengerCreateInfo(debugCreateInfo);
	createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
#endif

	createInfo.enabledLayerCount = 0;
	createInfo.pNext = nullptr;

	std::vector<const char*> requiredExtensions;

	for (uint32_t i = 0; i < extensions.size(); i++)
	{
		requiredExtensions.emplace_back(extensions[i]);
	}
#if defined(__APPLE__) && defined(__MACH__)
	requiredExtensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
	createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
#endif
	createInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
	createInfo.ppEnabledExtensionNames = requiredExtensions.data();

	if (vkCreateInstance(&createInfo, nullptr, &inst) != VK_SUCCESS)
		throw std::runtime_error("Failed to create instance!");

	uint32_t vkExtCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &vkExtCount, nullptr);
	if (!vkExtCount)
	{
		LOG_WARNING("No available extensions\n");
	}
	else {
		std::vector<VkExtensionProperties> vkExtensions(vkExtCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &vkExtCount, vkExtensions.data());
		std::string msg = std::to_string(vkExtCount) + " extensions available: \n";
		for (const auto& ext : vkExtensions)
			msg += "\t\t" + std::string(ext.extensionName) + "\n";
		LOG_INFO(msg.c_str());
	}

	return;
}

VkInstance& KInstance::get()
{
	return inst;
}
