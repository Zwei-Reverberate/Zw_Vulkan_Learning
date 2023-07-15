#ifndef VKCORELOGICALDEVICE_H
#define VKCORELOGICALDEVICE_H
#include "../vkcore/vkcorephysicaldevice.h"
#include "../vkcore/vkcoresurface.h"

class VkcoreLogicalDevice
{
private:
	VkDevice m_device;
	VkQueue m_graphicsQueue;
	VkQueue m_presentQueue;
public:
	VkcoreLogicalDevice() = default;
	~VkcoreLogicalDevice() = default;
	void create(std::shared_ptr<VkcorePhysicalDevice> pCorePhysicalDevice, std::shared_ptr<VkcoreSurface> pSurface);
	void destroy();
	VkDevice getDevice();
	VkQueue getGraphicsQueue();
	VkQueue getPresentQueue();
	void waiteIdle();
};


#endif // !VKCORELOGICALDEVICE_H

