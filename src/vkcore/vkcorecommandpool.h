#ifndef VKCORECOMMANDPOOL_H
#define VKCORECOMMANDPOOL_H
#include "../vkcore/vkcorephysicaldevice.h"
#include "../vkcore/vkcorelogicaldevice.h"
#include "../vkcore/vkcoresurface.h"

class VkcoreCommndPool
{
private:
	VkCommandPool m_commandPool;

public:
	VkcoreCommndPool() = default;
	~VkcoreCommndPool() = default;

	void create(std::shared_ptr<VkcorePhysicalDevice> pPhysicalDevice, std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice, std::shared_ptr<VkcoreSurface> pSurface);
	void destroy(std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice);
	VkCommandPool getCommandPool();
};

#endif // !VKCORECOMMANDPOOL_H
