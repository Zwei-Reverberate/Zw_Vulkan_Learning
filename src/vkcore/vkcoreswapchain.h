#ifndef VKCORESWAPCHAIN_H
#define VKCORESWAPCHAIN_H
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include "../vkcore/vkcorephysicaldevice.h"
#include "../vkcore/swapchainsupportdetails.h"
#include "../vkcore/vkcorelogicaldevice.h"

class VkcoreSwapChain
{
private:
	VkSwapchainKHR m_swapChain;
	std::vector<VkImage> m_swapChainImages;
	VkFormat m_swapChainImageFormat;
	VkExtent2D m_swapChainExtent;

public:
	VkcoreSwapChain() = default;
	~VkcoreSwapChain() = default;

	VkSwapchainKHR getSwapChain() const;
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow* window);
	void create(GLFWwindow* pWindow, std::shared_ptr<VkcorePhysicalDevice> pPhysicalDevice, std::shared_ptr<VkcoreSurface> pSurface, std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice);
	void destroy(std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice);

	std::vector<VkImage> getSwapChainImages() const;
	VkFormat getSwapChainImageFormat() const;
	VkExtent2D getSwapChainExtent() const;
};

#endif // !VKCORESWAPCHAIN_H