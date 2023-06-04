#include "vkcoresurface.h"
#include <stdexcept>

VkSurfaceKHR VkcoreSurface::getSurface()
{
	return m_surface;
}

void VkcoreSurface::create(std::shared_ptr<VkcoreInstance> pInstance, GlfwWdindow* pWindow)
{
	if (!pInstance || !pWindow)
	{
		return;
	}

	if (glfwCreateWindowSurface(pInstance->getInstance(), pWindow->getWindow(), nullptr, &m_surface) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create window surface!");
	}
}

void VkcoreSurface::destroy(std::shared_ptr<VkcoreInstance> pInstance)
{
	if (!pInstance)
	{
		return;
	}
	vkDestroySurfaceKHR(pInstance->getInstance(), m_surface, nullptr);
}
