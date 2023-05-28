#include "vkcoreinstance.h"
#include "../enum/appenum.h"
#include <stdexcept>
#include <memory>

void VkcoreInstance::create()
{
    // 在创建之前检查所有的 validation layers 是否可用
    if (appenum::enableValidationLayers && !VkValidation::checkValidationLayerSupport()) 
    {
        throw std::runtime_error("validation layers requested, but not available!");
    }

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = appenum::APPLICATION_NAME;
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = appenum::ENGINE_NAME;
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    auto extensions = VkValidation::getRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    if (appenum::enableValidationLayers) 
    {
        createInfo.enabledLayerCount = static_cast<uint32_t>(appenum::validationLayers.size());
        createInfo.ppEnabledLayerNames = appenum::validationLayers.data();
        m_validation.populateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
    }
    else 
    {
        createInfo.enabledLayerCount = 0;
        createInfo.pNext = nullptr;
    }

    if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS) 
    {
        throw std::runtime_error("failed to create instance!");
    }
}

void VkcoreInstance::destroy()
{
    if (appenum::enableValidationLayers)
    {
        DestroyDebugUtilsMessengerEXT(m_instance, m_validation.getDebugMessenger(), nullptr);
    }
    vkDestroyInstance(m_instance, nullptr);
}

VkInstance VkcoreInstance::getInstance() const
{
    return m_instance;
}

VkValidation VkcoreInstance::getValidation() const
{
    return m_validation;
}

void VkcoreInstance::setupDebugMessenger()
{
    if (!appenum::enableValidationLayers) return;

    VkDebugUtilsMessengerCreateInfoEXT createInfo;
    m_validation.populateDebugMessengerCreateInfo(createInfo);

    VkDebugUtilsMessengerEXT debugMessenger = m_validation.getDebugMessenger();

    if (CreateDebugUtilsMessengerEXT(m_instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) 
    {
        throw std::runtime_error("failed to set up debug messenger!");
    }
    m_validation.setDebugMessenger(debugMessenger); // 在 destroy() 中需要用到
}

VkResult VkcoreInstance::CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger)
{
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) 
    {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    }
    else 
    {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void VkcoreInstance::DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator)
{
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) 
    {
        func(instance, debugMessenger, pAllocator);
    }
}
