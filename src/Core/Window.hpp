#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <string_view>
#include <vector>

#include "Utils/Logger.hpp"

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

class KInstance;

struct WindowSpecification
{
	int width = 0;
	int height = 0;
	std::string title = "";

	WindowSpecification() = default;
	WindowSpecification(int width, int height, std::string_view title) : width(width), height(height), title(title) {}
	~WindowSpecification() = default;
};

class Window
{
public:
	Window() = default;
	Window(WindowSpecification&& spec);
	~Window();

public:
	void create();

public:
	inline VkSurfaceKHR& getWinSurface() { return surface; }

	int getWidth() const { return m_spec.width; }
	int getHeight() const { return m_spec.height; }
	const char* getTitle() const { return std::string_view{ m_spec.title }.data(); }

public:
	inline operator GLFWwindow*() const { return window; }

public:
	void createSurface(KInstance& instance);
	void destroySurface(KInstance& instance);

private:
	static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

private:
	WindowSpecification m_spec;
	GLFWwindow* window = nullptr;

	VkSurfaceKHR surface{};
};

#endif