#include "vkcoresynchronization.h"
#include <stdexcept>

void VkcoreSynchronization::create(std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice)
{
	if (!pLogicalDevice)
	{
		return;
	}

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
    if (vkCreateSemaphore(pLogicalDevice->getDevice(), &semaphoreInfo, nullptr, &m_imageAvailableSemaphore) != VK_SUCCESS ||
        vkCreateSemaphore(pLogicalDevice->getDevice(), &semaphoreInfo, nullptr, &m_renderFinishedSemaphore) != VK_SUCCESS ||
        vkCreateFence(pLogicalDevice->getDevice(), &fenceInfo, nullptr, &m_inFlightFence) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create synchronization objects for a frame!");
    }
}

void VkcoreSynchronization::destroy(std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice)
{
    if (!pLogicalDevice)
    {
        return;
    }
    vkDestroySemaphore(pLogicalDevice->getDevice(), m_renderFinishedSemaphore, nullptr);
    vkDestroySemaphore(pLogicalDevice->getDevice(), m_imageAvailableSemaphore, nullptr);
    vkDestroyFence(pLogicalDevice->getDevice(), m_inFlightFence, nullptr);
}

VkFence& VkcoreSynchronization::getInFlightFence()
{
    return m_inFlightFence;
}

VkSemaphore VkcoreSynchronization::getImageAvailableSemaphore()
{
    return m_imageAvailableSemaphore;
}

VkSemaphore VkcoreSynchronization::getRenderFinishedSemaphore()
{
    return m_renderFinishedSemaphore;
}
