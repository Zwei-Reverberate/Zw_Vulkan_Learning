#ifndef VKVALIDATION_H
#define VKVALIDATION_H
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>

class VkValidation
{

private:
    VkDebugUtilsMessengerEXT m_debugMessenger; // 用于存储回调函数信息

public:
    VkDebugUtilsMessengerEXT getDebugMessenger() const;
    void setDebugMessenger(const VkDebugUtilsMessengerEXT& debugMessenger);
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

public:
	static bool checkValidationLayerSupport();
	static std::vector<const char*> getRequiredExtensions();

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback
    (
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData
    ); // 回调函数
};


#endif