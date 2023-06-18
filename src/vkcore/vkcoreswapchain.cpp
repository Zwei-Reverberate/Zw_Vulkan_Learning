#include "vkcoreswapchain.h"
#include <limits>
#include <algorithm> 
#include <stdexcept>

VkSwapchainKHR VkcoreSwapChain::getSwapChain() const
{
	return m_swapChain;
}

VkSurfaceFormatKHR VkcoreSwapChain::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
{
    for (const auto& availableFormat : availableFormats) 
    {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) 
        {
            return availableFormat;
        }
    }
    return availableFormats[0];
}

VkPresentModeKHR VkcoreSwapChain::chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
{
    // ����ʹ�� VK_PRESENT_MODE_MAILBOX_KHR������ʹ�� VK_PRESENT_MODE_FIFO_KHR
    for (const auto& availablePresentMode : availablePresentModes) 
    {
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) 
        {
            return availablePresentMode;
        }
    }
    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D VkcoreSwapChain::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow*window)
{
    if (!window)
    {
        return VkExtent2D();
    }

    if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) 
    {
        return capabilities.currentExtent;
    }
    else 
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        VkExtent2D actualExtent = 
        {
            static_cast<uint32_t>(width),
            static_cast<uint32_t>(height)
        };

        actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
        actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

        return actualExtent;
    }
}

void VkcoreSwapChain::create(GLFWwindow* pWindow, std::shared_ptr<VkcorePhysicalDevice> pPhysicalDevice, std::shared_ptr<VkcoreSurface> pSurface, std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice)
{
    if (!pWindow || !pPhysicalDevice || !pSurface || !pLogicalDevice)
    {
        return;
    }

    SwapChainSupportDetails swapChainSupport = SwapChainSupportDetails::querySwapChainSupport(pPhysicalDevice->getPhysicalDevice(), pSurface->getSurface());

    // ���� swap chain ����
    VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
    VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
    VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities, pWindow);

    // �趨 swap chain �е� image ����
    uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
    if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) 
    {
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }

    // ��䴴���� createInfo
    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = pSurface->getSurface();
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1; // ָ��ÿ�� image �����Ĳ���
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; // ָ����ʹ�� swap chain �е� image ���к��ֲ���

    // ��������ʹ�õ� swap chain images
    QueueFamilyIndices indices = QueueFamilyIndices::findQueueFamilies(pPhysicalDevice->getPhysicalDevice(), pSurface);
    uint32_t queueFamilyIndices[] = { indices.m_graphicsFamily.value(), indices.m_presentFamily.value() };
    if (indices.m_graphicsFamily != indices.m_presentFamily) 
    {
        // image �ɵ��� queue family ����
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    }
    else 
    {
        // image �����ʹ��
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        // createInfo.queueFamilyIndexCount = 0; // Optional
        // createInfo.pQueueFamilyIndices = nullptr; // Optional
    }

    createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;


    createInfo.oldSwapchain = VK_NULL_HANDLE;
    if (vkCreateSwapchainKHR(pLogicalDevice->getDevice(), &createInfo, nullptr, &m_swapChain) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create swap chain!");
    }

    vkGetSwapchainImagesKHR(pLogicalDevice->getDevice(), m_swapChain, &imageCount, nullptr);
    m_swapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(pLogicalDevice->getDevice(), m_swapChain, &imageCount, m_swapChainImages.data());
    m_swapChainImageFormat = surfaceFormat.format;
    m_swapChainExtent = extent;
}

void VkcoreSwapChain::destroy(std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice)
{
    if (!pLogicalDevice)
    {
        return;
    }
    vkDestroySwapchainKHR(pLogicalDevice->getDevice(), m_swapChain, nullptr);
}

std::vector<VkImage> VkcoreSwapChain::getSwapChainImages() const
{
    return m_swapChainImages;
}

VkFormat VkcoreSwapChain::getSwapChainImageFormat() const
{
    return m_swapChainImageFormat;
}

VkExtent2D VkcoreSwapChain::getSwapChainExtent() const
{
    return m_swapChainExtent;
}
