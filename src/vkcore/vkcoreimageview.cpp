#include "../vkcore/vkcoreimageview.h"
#include <stdexcept>

std::vector<VkImageView> VkcoreImageView::getSwapChainImageViews() const
{
	return m_swapChainImageViews;
}

void VkcoreImageView::create(std::shared_ptr<VkcoreSwapChain> pSwapChain, std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice)
{
	if (!pSwapChain || !pLogicalDevice)
	{
		return;
	}

    std::vector<VkImage> swapChainImages = pSwapChain->getSwapChainImages();
    m_swapChainImageViews.resize(swapChainImages.size());
    for (size_t i = 0; i < swapChainImages.size(); i++) 
    {
        VkImageViewCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image = swapChainImages[i];
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format = pSwapChain->getSwapChainImageFormat();
        createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;

        if (vkCreateImageView(pLogicalDevice->getDevice(), &createInfo, nullptr, &m_swapChainImageViews[i]) != VK_SUCCESS) 
        {
            throw std::runtime_error("failed to create image views!");
        }
    }
}

void VkcoreImageView::destroy(std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice)
{
    if (!pLogicalDevice)
    {
        return;
    }

    for (auto imageView : m_swapChainImageViews) 
    {
        vkDestroyImageView(pLogicalDevice->getDevice(), imageView, nullptr);
    }
}
