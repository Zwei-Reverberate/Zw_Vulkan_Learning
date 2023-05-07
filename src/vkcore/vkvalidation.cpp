#include "vkvalidation.h"
#include "../enum/appenum.h"
#include <vector>
#include <iostream>

VkDebugUtilsMessengerEXT VkValidation::getDebugMessenger() const
{
    return m_debugMessenger;
}

void VkValidation::setDebugMessenger(const VkDebugUtilsMessengerEXT& debugMessenger)
{
    m_debugMessenger = debugMessenger;
}

void VkValidation::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
{
    createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = debugCallback;
    createInfo.pUserData = nullptr; // Optional
}

// 检查所有的 validation layers 是否可用
bool VkValidation::checkValidationLayerSupport()
{
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char* layerName : appenum::validationLayers)
    {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers) 
        {
            if (strcmp(layerName, layerProperties.layerName) == 0) 
            {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) 
        {
            return false;
        }
    }
    return true;
}

// 根据是否启用 validation layers 返回需要的 extension 列表
std::vector<const char*> VkValidation::getRequiredExtensions()
{
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    if (appenum::enableValidationLayers) 
    {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
}

// 接受调试信息的回调函数
VKAPI_ATTR VkBool32 VKAPI_CALL VkValidation::debugCallback
(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, 
    VkDebugUtilsMessageTypeFlagsEXT messageType, 
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, 
    void* pUserData
)
{
    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
    return VK_FALSE;
}
