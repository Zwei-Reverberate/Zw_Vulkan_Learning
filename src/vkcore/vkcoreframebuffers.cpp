#include "vkcoreframebuffers.h"
#include <stdexcept>

void VkcoreFrameBuffers::create(std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice, std::shared_ptr<VkcoreRenderPass> pRenderPass, std::shared_ptr<VkcoreSwapChain> pSwapChain, std::shared_ptr<VkcoreImageView> pImageView)
{
	if (!pLogicalDevice || !pRenderPass || !pSwapChain || !pImageView)
	{
		return;
	}

    std::vector<VkImageView> swapChainImageViews = pImageView->getSwapChainImageViews();
    m_swapChainFramebuffers.resize(swapChainImageViews.size());

    // 为 swap chain 的每一个 image view 创建对应的 framebuffer
    for (size_t i = 0; i < pSwapChain->getSwapChainImages().size(); i++)
    {
        VkImageView attachments[] =
        {
            swapChainImageViews[i]
        };

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = pRenderPass->getRenderPass();
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = attachments;
        framebufferInfo.width = pSwapChain->getSwapChainExtent().width;
        framebufferInfo.height = pSwapChain->getSwapChainExtent().height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(pLogicalDevice->getDevice(), &framebufferInfo, nullptr, &m_swapChainFramebuffers[i]) != VK_SUCCESS) 
        {
            throw std::runtime_error("failed to create framebuffer!");
        }
    }
}

void VkcoreFrameBuffers::destroy(std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice)
{
	if (!pLogicalDevice)
	{
		return;
	}
    for (auto m_framebuffer : m_swapChainFramebuffers) 
    {
        vkDestroyFramebuffer(pLogicalDevice->getDevice(), m_framebuffer, nullptr);
    }

}

std::vector<VkFramebuffer> VkcoreFrameBuffers::getFrameBuffers()
{
    return m_swapChainFramebuffers;
}
