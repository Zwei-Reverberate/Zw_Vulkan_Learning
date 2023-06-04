#include "queuefamilyindices.h"
#include <vector>

bool QueueFamilyIndices::isComplete()
{
	return m_graphicsFamily.has_value();
}

QueueFamilyIndices QueueFamilyIndices::findQueueFamilies(VkPhysicalDevice device, std::shared_ptr<VkcoreSurface> pSurface)
{
    if (!pSurface)
    {
        return QueueFamilyIndices();
    }
    QueueFamilyIndices indices;
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto& queueFamily : queueFamilies) 
    {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) // 寻找一个支持图形 commands 的 queue family
        {
            indices.m_graphicsFamily = i;
        }

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, pSurface->getSurface(), &presentSupport);
        if (presentSupport) 
        {
            indices.m_presentFamily = i;
        }


        if (indices.isComplete()) 
        {
            break;
        }

        i++;
    }
    return indices;
}
