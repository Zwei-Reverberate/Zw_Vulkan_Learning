#include "vulkanapp.h"

void VulkanApp::excute()
{
	m_appWindow.initWindow();
	mainLoop();
	cleanUp();
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
	m_appWindow.destroyWindow();
}
