#ifndef VKCOREPHYSICALDEVICE_H
#define VKCOREPHYSICALDEVICE_H
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <memory>
#include "../vkcore/vkcoreinstance.h"
#include "../vkcore/queuefamilyindices.h"
#include "../vkcore/vkcoresurface.h"

class VkcorePhysicalDevice
{
private:
	VkPhysicalDevice m_physicalDevice;

public:
	VkcorePhysicalDevice();
	~VkcorePhysicalDevice() = default;
	VkPhysicalDevice getPhysicalDevice();
	void pickPhysicalDevice(std::shared_ptr<VkcoreInstance> pInstance, std::shared_ptr<VkcoreSurface> pSurface);
	bool isDeviceSuitable(VkPhysicalDevice device, std::shared_ptr<VkcoreSurface> pSurface);
};


#endif // !VKCOREPHYSICALDEVICE_H
