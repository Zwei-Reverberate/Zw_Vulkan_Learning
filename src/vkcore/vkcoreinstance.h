#ifndef VKCOREINSTANCE_H
#define VKCOREINSTANCE_H
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "../vkcore/vkvalidation.h"

class VkcoreInstance
{
private:
	VkInstance m_instance;
	VkValidation m_validation;

public:
	VkcoreInstance() = default;
	~VkcoreInstance() = default;
	
	void create();
	void destroy();
	VkInstance getInstance() const;
	VkValidation getValidation() const;

	void setupDebugMessenger();
	static VkResult CreateDebugUtilsMessengerEXT
	(
		VkInstance instance, 
		const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, 
		const VkAllocationCallbacks* pAllocator, 
		VkDebugUtilsMessengerEXT* pDebugMessenger
	);
	static void DestroyDebugUtilsMessengerEXT
	(
		VkInstance instance, 
		VkDebugUtilsMessengerEXT debugMessenger, 
		const VkAllocationCallbacks* pAllocator
	);
};

#endif // !VKCOREINSTANCE_H

