#include "vkcorecommandbuffer.h"
#include <stdexcept>

void VkcoreCommandBuffer::create(std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice, std::shared_ptr<VkcoreCommndPool> pCommandPool)
{
	if (!pLogicalDevice || !pCommandPool)
	{
		return;
	}
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = pCommandPool->getCommandPool(); // ָ�� commandPool
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY; // ָ������ command buffer ���Ǹ��� command buffer���˴����� command buffer
    allocInfo.commandBufferCount = 1; // ָ�����������

    if (vkAllocateCommandBuffers(pLogicalDevice->getDevice(), &allocInfo, &m_commandBuffer) != VK_SUCCESS) 
    {
        throw std::runtime_error("failed to allocate command buffers!");
    }
}

void VkcoreCommandBuffer::recordCommandBuffer(uint32_t imageIndex, std::shared_ptr<VkcoreRenderPass> pRenderPass, std::shared_ptr<VkcoreFrameBuffers> pFramebuffers, std::shared_ptr<VkcoreGraphicsPipeline> pGraphicsPipeline, std::shared_ptr<VkcoreSwapChain> pSwapChain)
{
    if (!pRenderPass || !pFramebuffers || !pGraphicsPipeline || !pSwapChain)
    {
        return;
    }

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    if (vkBeginCommandBuffer(m_commandBuffer, &beginInfo) != VK_SUCCESS) 
    {
        throw std::runtime_error("failed to begin recording command buffer!");
    }

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = pRenderPass->getRenderPass();
    renderPassInfo.framebuffer = pFramebuffers->getFrameBuffers()[imageIndex];
    renderPassInfo.renderArea.offset = { 0, 0 };
    renderPassInfo.renderArea.extent = pSwapChain->getSwapChainExtent();

    VkClearValue clearColor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &clearColor;
    vkCmdBeginRenderPass(m_commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindPipeline(m_commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pGraphicsPipeline->getGraphicsPipeline());
    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float)pSwapChain->getSwapChainExtent().width;
    viewport.height = (float)pSwapChain->getSwapChainExtent().height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    vkCmdSetViewport(m_commandBuffer, 0, 1, &viewport);

    VkRect2D scissor{};
    scissor.offset = { 0, 0 };
    scissor.extent = pSwapChain->getSwapChainExtent();
    vkCmdSetScissor(m_commandBuffer, 0, 1, &scissor);

    vkCmdDraw(m_commandBuffer, 3, 1, 0, 0);
    vkCmdEndRenderPass(m_commandBuffer);
    if (vkEndCommandBuffer(m_commandBuffer) != VK_SUCCESS) 
    {
        throw std::runtime_error("failed to record command buffer!");
    }
}

VkCommandBuffer& VkcoreCommandBuffer::getCommandBuffer()
{
    return m_commandBuffer;
}
