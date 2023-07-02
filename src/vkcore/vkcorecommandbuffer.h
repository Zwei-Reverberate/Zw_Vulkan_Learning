#ifndef VKCORECOMMANDBUFFER_H
#define VKCORECOMMANDBUFFER_H
#include "../vkcore/vkcorelogicaldevice.h"
#include "../vkcore/vkcorecommandpool.h"
#include "../vkcore/vkcoreframebuffers.h"
#include "../graphicspipeline/vkcoregraphicspipeline.h"
#include "../graphicspipeline/vkcorerenderpass.h"

class VkcoreCommandBuffer
{
private:
	VkCommandBuffer m_commandBuffer;

public:
	VkcoreCommandBuffer() = default;
	~VkcoreCommandBuffer() = default;
	void create(std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice, std::shared_ptr<VkcoreCommndPool> pCommandPool);
	void recordCommandBuffer(uint32_t imageIndex, std::shared_ptr<VkcoreRenderPass> pRenderPass, std::shared_ptr<VkcoreFrameBuffers> pFramebuffers, std::shared_ptr<VkcoreGraphicsPipeline> pGraphicsPipeline, std::shared_ptr<VkcoreSwapChain> pSwapChain);
	VkCommandBuffer& getCommandBuffer();
};

#endif // !VKCORECOMMANDBUFFER_H
