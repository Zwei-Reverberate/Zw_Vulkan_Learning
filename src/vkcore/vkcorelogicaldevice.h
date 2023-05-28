#ifndef VKCORELOGICALDEVICE_H
#define VKCORELOGICALDEVICE_H
#include "../vkcore/vkcorephysicaldevice.h"

class VkcoreLogicalDevice
{
private:
	VkDevice m_device;
	VkQueue m_graphicsQueue;
public:
	VkcoreLogicalDevice() = default;
	~VkcoreLogicalDevice() = default;
	void create(std::shared_ptr<VkcorePhysicalDevice> pCorePhysicalDevice);
	void destroy();
	VkDevice getDevice();
};


#endif // !VKCORELOGICALDEVICE_H

