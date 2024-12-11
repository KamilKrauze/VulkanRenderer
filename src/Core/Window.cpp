#include "Core/Window.hpp"
#include "Core/DebugMessenger.hpp"

Window::Window(WindowSpecification&& spec)
{
	this->m_spec = std::move(spec);

	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	window = glfwCreateWindow(m_spec.width, m_spec.height, "Vulkan", nullptr, nullptr);
	if (!window) {
		LOG_ERROR("Failed window creation!\n");
		glfwTerminate();
	}

	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);

	LOG_SUCCESS("Created window!");
}

Window::~Window()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::createSurface(KInstance& instance)
{
	VkWin32SurfaceCreateInfoKHR createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	createInfo.hwnd = glfwGetWin32Window(window);
	createInfo.hinstance = GetModuleHandle(nullptr);

	if (vkCreateWin32SurfaceKHR(instance.get(), &createInfo, nullptr, &surface) != VK_SUCCESS)
		throw std::runtime_error("Failed to create window surface!");

	LOG_SUCCESS("Surface successfully created!");
}

void Window::destroySurface(KInstance& instance)
{
	vkDestroySurfaceKHR(instance.get(), surface, nullptr);
}

void Window::framebufferResizeCallback(GLFWwindow* window, int width, int height)
{
	//frameBufferResized = true;
}
