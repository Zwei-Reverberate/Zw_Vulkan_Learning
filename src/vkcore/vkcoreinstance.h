#ifndef VKCOREINSTANCE_H
#define VKCOREINSTANCE_H
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_INCLUDE_VULKAN

class VkcoreInstance
{
private:
	VkInstance m_instance;

public:
	VkcoreInstance() = default;
	~VkcoreInstance() = default;
	
	void create();
	void destroy();
	VkInstance getInstance() const;
};

#endif // !VKCOREINSTANCE_H

