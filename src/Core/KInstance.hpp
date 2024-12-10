#ifndef K_INST_HPP
#define K_INST_HPP

#include <string_view>

#include <vulkan/vulkan.h>

/// <summary>
/// Krauze Renderer Instance
/// </summary>
class KInstance
{
public:
	KInstance() = default;
	~KInstance() = default;

private:
	VkInstance inst;
};

class AppInfoBuilder
{
public:
	AppInfoBuilder();
	~AppInfoBuilder() = default;
public:
	AppInfoBuilder& setAppName(std::string_view name);
	AppInfoBuilder& setEngineName(std::string_view name);
	AppInfoBuilder& setApplicationVersion(uint32_t version);
	AppInfoBuilder& setEngineVersion(uint32_t version);
	AppInfoBuilder& setAPIVersion(uint32_t version);
	VkApplicationInfo& get();

private:
	VkApplicationInfo appInfo{};
};

#endif // !K_INST_HPP


