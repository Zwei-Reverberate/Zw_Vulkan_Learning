#ifndef VKCOREFRAMEBUFFERS_H
#define VKCOREFRAMEBUFFERS_H
#include <vector>
#include "../vkcore/vkcorelogicaldevice.h"
#include "../vkcore/vkcoreswapchain.h"
#include "../vkcore/vkcoreimageview.h"
#include "../graphicspipeline/vkcorerenderpass.h"

class VkcoreFrameBuffers
{
private:
	std::vector<VkFramebuffer> m_swapChainFramebuffers;

public:
	VkcoreFrameBuffers() = default;
	~VkcoreFrameBuffers() = default;
	void create(std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice, std::shared_ptr<VkcoreRenderPass> pRenderPass, std::shared_ptr<VkcoreSwapChain> pSwapChain, std::shared_ptr<VkcoreImageView> pImageView);
	void destroy(std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice);
};

#endif // !VKCORERFRAMEBUFFER_H
