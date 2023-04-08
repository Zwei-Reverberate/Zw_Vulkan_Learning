#ifndef VULKANAPP_H
#define VULKANAPP_H
#include "glfwwindow.h"

class VulkanApp
{
private:
	GlfwWdindow m_appWindow;

public:
	void excute();
	void mainLoop();
	void cleanUp();
};

#endif // !VULKANAPP_H
