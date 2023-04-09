#ifndef VULKANAPP_H
#define VULKANAPP_H
#include <memory>
#include "glfwwindow.h"
#include "../vkcore/vkcoreinstance.h"

class VulkanApp
{
private:
	GlfwWdindow m_appWindow;

	std::shared_ptr<VkcoreInstance> m_coreInstance;

public:
	void excute();
	void initCoreVulkan();
	void mainLoop();
	void cleanUp();
};

#endif // !VULKANAPP_H
