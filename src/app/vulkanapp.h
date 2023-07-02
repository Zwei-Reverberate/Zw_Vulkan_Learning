#ifndef VULKANAPP_H
#define VULKANAPP_H
#include <memory>
#include "glfwwindow.h"
#include "../vkcore/vkcoreinstance.h"
#include "../vkcore/vkcorephysicaldevice.h"
#include "../vkcore/vkcorelogicaldevice.h"
#include "../vkcore/vkcoresurface.h"
#include "../vkcore/vkcoreswapchain.h"
#include "../vkcore/vkcoreimageview.h"
#include "../vkcore/vkcoreframebuffers.h"
#include "../vkcore/vkcorecommandpool.h"
#include "../vkcore/vkcorecommandbuffer.h"
#include "../vkcore/vkcoresynchronization.h"
#include "../graphicspipeline/vkcoregraphicspipeline.h"
#include "../graphicspipeline/vkcorerenderpass.h"

class VulkanApp
{
private:
	GlfwWdindow m_appWindow;
	std::shared_ptr<VkcoreInstance> m_coreInstance;
	std::shared_ptr<VkcorePhysicalDevice> m_corePhysicalDevice;
	std::shared_ptr<VkcoreLogicalDevice> m_coreLogicalDevice;
	std::shared_ptr<VkcoreSurface> m_coreSurface;
	std::shared_ptr<VkcoreSwapChain> m_coreSwapChain;
	std::shared_ptr<VkcoreImageView> m_coreImageView;
	std::shared_ptr<VkcoreRenderPass> m_coreRenderPass;
	std::shared_ptr<VkcoreGraphicsPipeline> m_coreGraphicsPipeline;
	std::shared_ptr<VkcoreFrameBuffers> m_coreFrameBuffers;
	std::shared_ptr<VkcoreCommndPool> m_coreCommndPool;
	std::shared_ptr<VkcoreCommandBuffer> m_coreCommandBuffer;
	std::shared_ptr<VkcoreSynchronization> m_coreSynchronization;

public:
	void excute();
	void initCoreVulkan();
	void mainLoop();
	void cleanUp();
	void drawFrame();
};

#endif // !VULKANAPP_H
