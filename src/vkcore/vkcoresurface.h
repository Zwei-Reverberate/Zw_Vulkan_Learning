#ifndef VKCORESURFACE_H
#define VKCORESURFACE_H
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <memory>
#include "../vkcore/vkcoreinstance.h"
#include "../app/glfwwindow.h"

class VkcoreSurface
{
private:
	VkSurfaceKHR m_surface;

public:
	VkcoreSurface() = default;
	~VkcoreSurface() = default;
	VkSurfaceKHR getSurface();

	void create(std::shared_ptr<VkcoreInstance> pInstance, GlfwWdindow* pWindow);
	void destroy(std::shared_ptr<VkcoreInstance> pInstance);
};

#endif // !VKCORESURFACE_H
