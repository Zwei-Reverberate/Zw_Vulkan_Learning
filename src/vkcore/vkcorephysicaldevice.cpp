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

bool VkcorePhysicalDevice::isDeviceSuitable(VkPhysicalDevice device)
{
    QueueFamilyIndices indices = QueueFamilyIndices::findQueueFamilies(device);
    return indices.isComplete();
}

void VkcorePhysicalDevice::pickPhysicalDevice(std::shared_ptr<VkcoreInstance> p_instance)
{
    if (!p_instance)
    {
        return;
    }

    // �����г��Կ��豸���Ӳ�ѯ��ſ�ʼ�����豸��Ϊ0�����׳��쳣
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(p_instance->getInstance(), &deviceCount, nullptr);
    if (deviceCount == 0) 
    {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    // �������һ���������������е� VkPhysicalDevice handle
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(p_instance->getInstance(), &deviceCount, devices.data());

    for (const auto& device : devices) 
    {
        if (isDeviceSuitable(device)) 
        {
            m_physicalDevice = device; // ѡ����������ĵ�һ���Կ�
            break;
        }
    }

    if (m_physicalDevice == VK_NULL_HANDLE) 
    {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}
