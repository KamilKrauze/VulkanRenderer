#include "KInstance.hpp"

AppInfoBuilder::AppInfoBuilder()
{
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
}

AppInfoBuilder& AppInfoBuilder::setAppName(std::string_view name)
{
    appInfo.pApplicationName = name.data();
    return *this;
}

AppInfoBuilder& AppInfoBuilder::setEngineName(std::string_view name)
{
    appInfo.pEngineName = name.data();
    return *this;
}

AppInfoBuilder& AppInfoBuilder::setApplicationVersion(uint32_t version)
{
    appInfo.applicationVersion = version;
    return *this;
}

AppInfoBuilder& AppInfoBuilder::setEngineVersion(uint32_t version)
{
    appInfo.engineVersion = version;
    return *this;
}

AppInfoBuilder& AppInfoBuilder::setAPIVersion(uint32_t version)
{
    appInfo.apiVersion = version;
    return *this;
}

VkApplicationInfo& AppInfoBuilder::get()
{
    return appInfo;
}
