#include "vkcorecommandpool.h"
#include<stdexcept>

void VkcoreCommndPool::create(std::shared_ptr<VkcorePhysicalDevice> pPhysicalDevice, std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice, std::shared_ptr<VkcoreSurface> pSurface)
{
	if (!pPhysicalDevice || !pLogicalDevice || !pSurface)
	{
		return;
	}

	QueueFamilyIndices queueFamilyIndices = QueueFamilyIndices::findQueueFamilies(pPhysicalDevice->getPhysicalDevice(), pSurface);

	VkCommandPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	poolInfo.queueFamilyIndex = queueFamilyIndices.m_graphicsFamily.value();
	if (vkCreateCommandPool(pLogicalDevice->getDevice(), &poolInfo, nullptr, &m_commandPool) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create command pool!");
	}
}

void VkcoreCommndPool::destroy(std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice)
{
	if (!pLogicalDevice)
	{
		return;
	}
	vkDestroyCommandPool(pLogicalDevice->getDevice(), m_commandPool, nullptr);
}

VkCommandPool VkcoreCommndPool::getCommandPool()
{
	return m_commandPool;
}
