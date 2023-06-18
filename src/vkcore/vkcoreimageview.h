#ifndef VKCOREIMAGEVIEW_H
#define VKCOREIMAGEVIEW_H
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include "../vkcore/vkcoreswapchain.h"

class VkcoreImageView
{
private:
	std::vector<VkImageView> m_swapChainImageViews;

public:
	VkcoreImageView() = default;
	~VkcoreImageView() = default;
	std::vector<VkImageView> getSwapChainImageViews() const;

	void create(std::shared_ptr<VkcoreSwapChain> pSwapChain, std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice);
	void destroy(std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice);
};

#endif // !VKIMAGEVIEW_H
