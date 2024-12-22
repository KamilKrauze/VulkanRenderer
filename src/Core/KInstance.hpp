#ifndef K_INST_HPP
#define K_INST_HPP

#include <string_view>

#include <vulkan/vulkan.h>

/// <summary>
/// Krauze Renderer Vulkan Instance Wrapper
/// </summary>
class KInstance
{
public:
	KInstance() = default;
	~KInstance() = default;

public:
	void create(VkApplicationInfo& appInfo);
    VkInstance& get();

private:
	VkInstance inst;
};

class AppInfoBuilder
{
public:
    AppInfoBuilder()
    {
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    }

	~AppInfoBuilder() = default;
public:
    AppInfoBuilder& setAppName(std::string_view name)
    {
        appInfo.pApplicationName = name.data();
        return *this;
    }

    AppInfoBuilder& setEngineName(std::string_view name)
    {
        appInfo.pEngineName = name.data();
        return *this;
    }

    AppInfoBuilder& setApplicationVersion(uint32_t version)
    {
        appInfo.applicationVersion = version;
        return *this;
    }

    AppInfoBuilder& setEngineVersion(uint32_t version)
    {
        appInfo.engineVersion = version;
        return *this;
    }

    AppInfoBuilder& setAPIVersion(uint32_t version)
    {
        appInfo.apiVersion = version;
        return *this;
    }

    VkApplicationInfo& get()
    {
        return appInfo;
    }

private:
	VkApplicationInfo appInfo{};
};

#endif // !K_INST_HPP


