#include "vulkanapp.h"

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

	m_corePhysicalDevice = std::make_shared<VkcorePhysicalDevice>();
	m_corePhysicalDevice->pickPhysicalDevice(m_coreInstance);

	m_coreLogicalDevice = std::make_shared<VkcoreLogicalDevice>();
	m_coreLogicalDevice->create(m_corePhysicalDevice);
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
	m_coreLogicalDevice->destroy();
	m_coreInstance->destroy();
	m_appWindow.destroyWindow();
}
