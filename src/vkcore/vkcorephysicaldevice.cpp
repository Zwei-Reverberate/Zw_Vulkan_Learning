#include "vkcorephysicaldevice.h"
#include <stdexcept>

VkcorePhysicalDevice::VkcorePhysicalDevice()
{
	m_physicalDevice = VK_NULL_HANDLE;
}

VkPhysicalDevice VkcorePhysicalDevice::getPhysicalDevice()
{
    return m_physicalDevice;
}

bool VkcorePhysicalDevice::isDeviceSuitable(VkPhysicalDevice device, std::shared_ptr<VkcoreSurface> pSurface)
{
    if (!pSurface)
    {
        return false;
    }
    QueueFamilyIndices indices = QueueFamilyIndices::findQueueFamilies(device, pSurface);
    return indices.isComplete();
}

void VkcorePhysicalDevice::pickPhysicalDevice(std::shared_ptr<VkcoreInstance> pInstance, std::shared_ptr<VkcoreSurface> pSurface)
{
    if (!pInstance || !pSurface)
    {
        return;
    }

    // 首先列出显卡设备。从查询编号开始。若设备数为0，则抛出异常
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(pInstance->getInstance(), &deviceCount, nullptr);
    if (deviceCount == 0) 
    {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    // 否则分配一个数组来保存所有的 VkPhysicalDevice handle
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(pInstance->getInstance(), &deviceCount, devices.data());

    for (const auto& device : devices) 
    {
        if (isDeviceSuitable(device, pSurface)) 
        {
            m_physicalDevice = device; // 选择满足需求的第一张显卡
            break;
        }
    }

    if (m_physicalDevice == VK_NULL_HANDLE) 
    {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}
