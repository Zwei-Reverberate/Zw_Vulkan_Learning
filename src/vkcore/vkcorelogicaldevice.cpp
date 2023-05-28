#include "../vkcore/vkcorelogicaldevice.h"
#include "../vkcore/queuefamilyindices.h"
#include "../enum/appenum.h"
#include <stdexcept>

void VkcoreLogicalDevice::create(std::shared_ptr<VkcorePhysicalDevice> pCorePhysicalDevice)
{
    if (!pCorePhysicalDevice)
    {
        return;
    }

    auto physicalDevice = pCorePhysicalDevice->getPhysicalDevice();
    QueueFamilyIndices indices = QueueFamilyIndices::findQueueFamilies(physicalDevice);

    VkDeviceQueueCreateInfo queueCreateInfo{}; // VkDeviceQueueCreateInfo 描述了单个 queue family 所需要的队列数
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = indices.m_graphicsFamily.value();
    queueCreateInfo.queueCount = 1;

    // 为 Queue 分配优先级以影响命令缓冲区执行的调度
    float queuePriority = 1.0f;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.queueCreateInfoCount = 1;

    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount = 0;

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
}

void VkcoreLogicalDevice::destroy()
{
    vkDestroyDevice(m_device, nullptr);
}

VkDevice VkcoreLogicalDevice::getDevice()
{
    return m_device;
}
