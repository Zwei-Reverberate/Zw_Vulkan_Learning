#include "vulkanapp.h"
#include "../enum/appenum.h"

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

	m_graphicsPipeline = std::make_shared<VkGraphicsPipeline>();
	m_graphicsPipeline->create(appenum::vertexShaderPath, appenum::fragmentShaderPath, m_coreLogicalDevice);
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
	}
}

void VulkanApp::cleanUp()
{
	m_coreImageView->destroy(m_coreLogicalDevice);
	m_coreSwapChain->destroy(m_coreLogicalDevice);
	m_coreLogicalDevice->destroy();
	m_coreSurface->destroy(m_coreInstance);
	m_coreInstance->destroy();
	m_appWindow.destroyWindow();
}
