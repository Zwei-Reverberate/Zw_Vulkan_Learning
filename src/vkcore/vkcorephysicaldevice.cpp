#include "vkcorephysicaldevice.h"
#include "../enum/appenum.h"
#include "../vkcore/swapchainsupportdetails.h"
#include <stdexcept>
#include <set>

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
    bool extensionsSupported = checkDeviceExtensionSupport(device);

    bool swapChainAdequate = false;
    if (extensionsSupported)
    {
        SwapChainSupportDetails swapChainSupport = SwapChainSupportDetails::querySwapChainSupport(device, pSurface->getSurface());
        swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
    }

    return indices.isComplete() && extensionsSupported && swapChainAdequate;
}

bool VkcorePhysicalDevice::checkDeviceExtensionSupport(VkPhysicalDevice device)
{
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

    std::set<std::string> requiredExtensions(appenum::deviceExtensions.begin(), appenum::deviceExtensions.end());

    for (const auto& extension : availableExtensions) 
    {
        requiredExtensions.erase(extension.extensionName);
    }
    return requiredExtensions.empty();
}

void VkcorePhysicalDevice::pickPhysicalDevice(std::shared_ptr<VkcoreInstance> pInstance, std::shared_ptr<VkcoreSurface> pSurface)
{
    if (!pInstance || !pSurface)
    {
        return;
    }

    // �����г��Կ��豸���Ӳ�ѯ��ſ�ʼ�����豸��Ϊ0�����׳��쳣
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(pInstance->getInstance(), &deviceCount, nullptr);
    if (deviceCount == 0) 
    {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    // �������һ���������������е� VkPhysicalDevice handle
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(pInstance->getInstance(), &deviceCount, devices.data());

    for (const auto& device : devices) 
    {
        if (isDeviceSuitable(device, pSurface)) 
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
