#include "VkcoreCommandBuffers.h"
#include "../enum/appenum.h"
#include <stdexcept>

void VkcoreCommandBuffers::create(std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice, std::shared_ptr<VkcoreCommndPool> pCommandPool)
{
	if (!pLogicalDevice || !pCommandPool)
	{
		return;
	}
    m_commandBuffers.resize(appenum::MAX_FRAMES_IN_FLIGHT);
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = pCommandPool->getCommandPool(); // 指定 commandPool
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY; // 指定是主 command buffer 还是辅助 command buffer，此处是主 command buffer
    allocInfo.commandBufferCount = (uint32_t)m_commandBuffers.size();; // 指定分配的数量

    if (vkAllocateCommandBuffers(pLogicalDevice->getDevice(), &allocInfo, m_commandBuffers.data()) != VK_SUCCESS) 
    {
        throw std::runtime_error("failed to allocate command buffers!");
    }
}

void VkcoreCommandBuffers::recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex, std::shared_ptr<VkcoreRenderPass> pRenderPass, std::shared_ptr<VkcoreFrameBuffers> pFramebuffers, std::shared_ptr<VkcoreGraphicsPipeline> pGraphicsPipeline, std::shared_ptr<VkcoreSwapChain> pSwapChain)
{
    if (!pRenderPass || !pFramebuffers || !pGraphicsPipeline || !pSwapChain)
    {
        return;
    }

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) 
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
    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pGraphicsPipeline->getGraphicsPipeline());
    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float)pSwapChain->getSwapChainExtent().width;
    viewport.height = (float)pSwapChain->getSwapChainExtent().height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

    VkRect2D scissor{};
    scissor.offset = { 0, 0 };
    scissor.extent = pSwapChain->getSwapChainExtent();
    vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

    vkCmdDraw(commandBuffer, 3, 1, 0, 0);
    vkCmdEndRenderPass(commandBuffer);
    if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) 
    {
        throw std::runtime_error("failed to record command buffer!");
    }
}

std::vector<VkCommandBuffer>& VkcoreCommandBuffers::getCommandBuffers()
{
    return m_commandBuffers;
}

