#include "vkcoresynchronization.h"
#include <stdexcept>
#include "../enum/appenum.h"

void VkcoreSynchronization::create(std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice)
{
	if (!pLogicalDevice)
	{
		return;
	}

    m_imageAvailableSemaphores.resize(appenum::MAX_FRAMES_IN_FLIGHT);
    m_renderFinishedSemaphores.resize(appenum::MAX_FRAMES_IN_FLIGHT);
    m_inFlightFences.resize(appenum::MAX_FRAMES_IN_FLIGHT);

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t i = 0; i < appenum::MAX_FRAMES_IN_FLIGHT; i++)
    {
        if (vkCreateSemaphore(pLogicalDevice->getDevice(), &semaphoreInfo, nullptr, &m_imageAvailableSemaphores[i]) != VK_SUCCESS ||
            vkCreateSemaphore(pLogicalDevice->getDevice(), &semaphoreInfo, nullptr, &m_renderFinishedSemaphores[i]) != VK_SUCCESS ||
            vkCreateFence(pLogicalDevice->getDevice(), &fenceInfo, nullptr, &m_inFlightFences[i]) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create synchronization objects for a frame!");
        }
    }
}

void VkcoreSynchronization::destroy(std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice)
{
    if (!pLogicalDevice)
    {
        return;
    }

    for (size_t i = 0; i < appenum::MAX_FRAMES_IN_FLIGHT; i++)
    {
        vkDestroySemaphore(pLogicalDevice->getDevice(), m_renderFinishedSemaphores[i], nullptr);
        vkDestroySemaphore(pLogicalDevice->getDevice(), m_imageAvailableSemaphores[i], nullptr);
        vkDestroyFence(pLogicalDevice->getDevice(), m_inFlightFences[i], nullptr);
    }
}

std::vector<VkFence>& VkcoreSynchronization::getInFlightFences()
{
    return m_inFlightFences;
}

std::vector<VkSemaphore> VkcoreSynchronization::getImageAvailableSemaphores()
{
    return m_imageAvailableSemaphores;
}

std::vector<VkSemaphore> VkcoreSynchronization::getRenderFinishedSemaphores()
{
    return m_renderFinishedSemaphores;
}
