#include "appenum.h"

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

	#ifdef NDEBUG
		const bool enableValidationLayers = false;
	#else
		const bool enableValidationLayers = true;
	#endif
}