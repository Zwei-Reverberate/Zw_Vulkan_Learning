#include "../vkcore/vkcorelogicaldevice.h"
#include "../vkcore/queuefamilyindices.h"
#include "../enum/appenum.h"
#include <stdexcept>
#include <vector>
#include <set>

void VkcoreLogicalDevice::create(std::shared_ptr<VkcorePhysicalDevice> pCorePhysicalDevice, std::shared_ptr<VkcoreSurface> pSurface)
{
    if (!pCorePhysicalDevice)
    {
        return;
    }

    auto physicalDevice = pCorePhysicalDevice->getPhysicalDevice();
    QueueFamilyIndices indices = QueueFamilyIndices::findQueueFamilies(physicalDevice, pSurface);

    // 使用一个 set 创建来自两个 queue family 的 queue
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = { indices.m_graphicsFamily.value(), indices.m_presentFamily.value() };
    float queuePriority = 1.0f;
    for (uint32_t queueFamily : uniqueQueueFamilies) 
    {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        // VkDeviceQueueCreateInfo 描述了单个 queue family 所需要的队列数
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.pEnabledFeatures = &deviceFeatures;
    // 启用 swap chain 需要 VK_KHR_swapchain 先启用扩展
    createInfo.enabledExtensionCount = static_cast<uint32_t>(appenum::deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = appenum::deviceExtensions.data();

    if (appenum::enableValidationLayers) 
    {
        createInfo.enabledLayerCount = static_cast<uint32_t>(appenum::validationLayers.size());
        createInfo.ppEnabledLayerNames = appenum::validationLayers.data();
    }
    else 
    {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &m_device) != VK_SUCCESS) 
    {
        throw std::runtime_error("failed to create logical device!");
    }

    vkGetDeviceQueue(m_device, indices.m_graphicsFamily.value(), 0, &m_graphicsQueue);
    vkGetDeviceQueue(m_device, indices.m_presentFamily.value(), 0, &m_presentQueue);
}

void VkcoreLogicalDevice::destroy()
{
    vkDestroyDevice(m_device, nullptr);
}

VkDevice VkcoreLogicalDevice::getDevice()
{
    return m_device;
}

VkQueue VkcoreLogicalDevice::getGraphicsQueue()
{
    return m_graphicsQueue;
}

VkQueue VkcoreLogicalDevice::getPresentQueue()
{
    return m_presentQueue;
}
