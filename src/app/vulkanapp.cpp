#include "vulkanapp.h"
#include "../enum/appenum.h"
#include <stdexcept>

void VulkanApp::recreateSwapChain()
{
	// 重新创建 swap chain
	int width = 0, height = 0;
	glfwGetFramebufferSize(m_appWindow.getWindow(), &width, &height);
	while (width == 0 || height == 0) // 处理窗口最小化的情况
	{
		glfwGetFramebufferSize(m_appWindow.getWindow(), &width, &height);
		glfwWaitEvents();
	}
	vkDeviceWaitIdle(m_coreLogicalDevice->getDevice()); // 不应触及仍在使用的资源
	cleanUpSwapChain();
	m_coreSwapChain->create(m_appWindow.getWindow(), m_corePhysicalDevice, m_coreSurface, m_coreLogicalDevice);
	m_coreImageView->create(m_coreSwapChain, m_coreLogicalDevice);
	m_coreFrameBuffers->create(m_coreLogicalDevice, m_coreRenderPass, m_coreSwapChain, m_coreImageView);
}

void VulkanApp::cleanUpSwapChain()
{
	m_coreFrameBuffers->destroy(m_coreLogicalDevice);
	m_coreImageView->destroy(m_coreLogicalDevice);
	m_coreSwapChain->destroy(m_coreLogicalDevice);
}

void VulkanApp::excute()
{
	m_appWindow.initWindow();
	initCoreVulkan();
	mainLoop();
	cleanUp();
}

void VulkanApp::initCoreVulkan()
{
	m_coreInstance = std::make_shared<VkcoreInstance>();
	m_coreInstance->create();
	m_coreInstance->setupDebugMessenger();

	m_coreSurface = std::make_shared<VkcoreSurface>();
	m_coreSurface->create(m_coreInstance, &m_appWindow);

	m_corePhysicalDevice = std::make_shared<VkcorePhysicalDevice>();
	m_corePhysicalDevice->pickPhysicalDevice(m_coreInstance, m_coreSurface);

	m_coreLogicalDevice = std::make_shared<VkcoreLogicalDevice>();
	m_coreLogicalDevice->create(m_corePhysicalDevice, m_coreSurface);

	m_coreSwapChain = std::make_shared<VkcoreSwapChain>();
	m_coreSwapChain->create(m_appWindow.getWindow(), m_corePhysicalDevice, m_coreSurface, m_coreLogicalDevice);

	m_coreImageView = std::make_shared<VkcoreImageView>();
	m_coreImageView->create(m_coreSwapChain, m_coreLogicalDevice);

	m_coreRenderPass = std::make_shared<VkcoreRenderPass>();
	m_coreRenderPass->create(m_coreLogicalDevice, m_coreSwapChain);
	
	m_coreGraphicsPipeline = std::make_shared<VkcoreGraphicsPipeline>();
	m_coreGraphicsPipeline->create(appenum::vertexShaderPath, appenum::fragmentShaderPath, m_coreLogicalDevice, m_coreRenderPass);

	m_coreFrameBuffers = std::make_shared<VkcoreFrameBuffers>();
	m_coreFrameBuffers->create(m_coreLogicalDevice, m_coreRenderPass, m_coreSwapChain, m_coreImageView);

	m_coreCommndPool = std::make_shared<VkcoreCommndPool>();
	m_coreCommndPool->create(m_corePhysicalDevice, m_coreLogicalDevice, m_coreSurface);

	m_coreVertexBuffer = std::make_shared<VkcoreVertexBuffer>();
	m_coreVertexBuffer->create(m_coreLogicalDevice, zwVertices, m_corePhysicalDevice);

	m_coreCommandBuffer = std::make_shared<VkcoreCommandBuffers>();
	m_coreCommandBuffer->create(m_coreLogicalDevice, m_coreCommndPool);

	m_coreSynchronization = std::make_shared<VkcoreSynchronization>();
	m_coreSynchronization->create(m_coreLogicalDevice);
}

void VulkanApp::mainLoop()
{
	GLFWwindow* window = m_appWindow.getWindow();
	if (!window)
	{
		return;
	}

	while (!glfwWindowShouldClose(window)) 
	{
		glfwPollEvents();
		drawFrame();
	}
	m_coreLogicalDevice->waiteIdle();
}

void VulkanApp::cleanUp()
{
	cleanUpSwapChain();
	m_coreGraphicsPipeline->destroy(m_coreLogicalDevice);
	m_coreRenderPass->destroy(m_coreLogicalDevice);
	m_coreVertexBuffer->destroy(m_coreLogicalDevice);
	m_coreSynchronization->destroy(m_coreLogicalDevice);
	m_coreCommndPool->destroy(m_coreLogicalDevice);
	m_coreLogicalDevice->destroy();
	m_coreSurface->destroy(m_coreInstance);
	m_coreInstance->destroy();
	m_appWindow.destroyWindow();
}

void VulkanApp::drawFrame()
{
	vkWaitForFences(m_coreLogicalDevice->getDevice(), 1, &m_coreSynchronization->getInFlightFences()[m_currentFrame], VK_TRUE, UINT64_MAX);

	// 从 swap chain 获取图像
	uint32_t imageIndex;
	VkResult result = vkAcquireNextImageKHR(m_coreLogicalDevice->getDevice(), m_coreSwapChain->getSwapChain(), UINT64_MAX, m_coreSynchronization->getImageAvailableSemaphores()[m_currentFrame], VK_NULL_HANDLE, &imageIndex);
	if (result == VK_ERROR_OUT_OF_DATE_KHR)
	{
		recreateSwapChain();
		return;
	}
	else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
	{
		throw std::runtime_error("failed to acquire swap chain image!");
	}
	// Only reset the fence if we are submitting work
	vkResetFences(m_coreLogicalDevice->getDevice(), 1, &m_coreSynchronization->getInFlightFences()[m_currentFrame]);

	// 记录 command buffer
	vkResetCommandBuffer(m_coreCommandBuffer->getCommandBuffers()[m_currentFrame], 0);
	m_coreCommandBuffer->recordCommandBuffer(m_coreCommandBuffer->getCommandBuffers()[m_currentFrame], imageIndex, m_coreRenderPass, m_coreFrameBuffers, m_coreGraphicsPipeline, m_coreSwapChain, m_coreVertexBuffer);

	// 提交 command buffer
	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	VkSemaphore waitSemaphores[] = { m_coreSynchronization->getImageAvailableSemaphores()[m_currentFrame] };
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &m_coreCommandBuffer->getCommandBuffers()[m_currentFrame];
	VkSemaphore signalSemaphores[] = { m_coreSynchronization->getRenderFinishedSemaphores()[m_currentFrame] };
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;
	if (vkQueueSubmit(m_coreLogicalDevice->getGraphicsQueue(), 1, &submitInfo, m_coreSynchronization->getInFlightFences()[m_currentFrame]) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to submit draw command buffer!");
	}

	// Presentation
	VkPresentInfoKHR presentInfo{};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;
	VkSwapchainKHR swapChains[] = { m_coreSwapChain->getSwapChain() };
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;
	presentInfo.pImageIndices = &imageIndex;
	result = vkQueuePresentKHR(m_coreLogicalDevice->getPresentQueue(), &presentInfo);
	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || m_appWindow.getIsFramebufferResized())
	{
		m_appWindow.setIsFramebufferResized(false);
		recreateSwapChain();
	}
	else if (result != VK_SUCCESS) 
	{
		throw std::runtime_error("failed to present swap chain image!");
	}


	// 每次都前进到下一帧
	m_currentFrame = (m_currentFrame + 1) % appenum::MAX_FRAMES_IN_FLIGHT;
}
