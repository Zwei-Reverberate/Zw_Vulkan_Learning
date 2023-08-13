#ifndef VkcoreCommandBuffers_H
#define VkcoreCommandBuffers_H
#include "vkcorelogicaldevice.h"
#include "vkcorecommandpool.h"
#include "vkcoreframebuffers.h"
#include "vkcorevertexbuffer.h"
#include "../graphicspipeline/vkcoregraphicspipeline.h"
#include "../graphicspipeline/vkcorerenderpass.h"
#include <vector>

class VkcoreCommandBuffers
{
private:
	std::vector<VkCommandBuffer> m_commandBuffers;

public:
	VkcoreCommandBuffers() = default;
	~VkcoreCommandBuffers() = default;
	void create(std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice, std::shared_ptr<VkcoreCommndPool> pCommandPool);
	std::vector<VkCommandBuffer>& getCommandBuffers();
	static void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex, std::shared_ptr<VkcoreRenderPass> pRenderPass, std::shared_ptr<VkcoreFrameBuffers> pFramebuffers, std::shared_ptr<VkcoreGraphicsPipeline> pGraphicsPipeline, std::shared_ptr<VkcoreSwapChain> pSwapChain, std::shared_ptr<VkcoreVertexBuffer> pVertexBuffer);
};

#endif // !VkcoreCommandBuffers_H
