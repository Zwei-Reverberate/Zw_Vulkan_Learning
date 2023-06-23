#include "appenum.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace appenum
{
	const int   GLFWWINDOW_WIDTH = 1280;
	const int   GLFWWINDOW_HEIGHT = 720;
	const char* GLFWWINDOW_NAME = "Zwei Vulkan";

	const char* APPLICATION_NAME = "Zwei Vulkan";
	const char* ENGINE_NAME = "No Engine";

	const std::vector<const char*> validationLayers = 
	{
		"VK_LAYER_KHRONOS_validation"
	};

	const std::vector<const char*> deviceExtensions = 
	{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	#ifdef NDEBUG
		const bool enableValidationLayers = false;
	#else
		const bool enableValidationLayers = true;
	#endif

	extern const std::string vertexShaderPath = "shader/triangle/trianglevert.spv";
	extern const std::string fragmentShaderPath = "shader/triangle/trianglefrag.spv";
}