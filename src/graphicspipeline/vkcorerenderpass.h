#ifndef VKCORERENDERPASS_H
#define VKCORERENDERPASS_H
#include "../vkcore/vkcorelogicaldevice.h"
#include "../vkcore/vkcoreswapchain.h"

class VkcoreRenderPass
{
private:
	VkRenderPass m_renderPass;
public:
	VkcoreRenderPass() = default;
	~VkcoreRenderPass() = default;
	void create(std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice, std::shared_ptr<VkcoreSwapChain> pSwapChain);
	void destroy(std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice);
	VkRenderPass getRenderPass();
};

#endif // !VKCORERENDERPASS_H
