#ifndef QUEUEFAMILYINDICES_H
#define QUEUEFAMILYINDICES_H
#define VKCOREPHYSICALDEVICE_H
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <optional>

struct QueueFamilyIndices
{
    std::optional<uint32_t> m_graphicsFamily;
    bool isComplete();

    // ��������� queue families
    static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
};
#endif // !QUEUEFAMILYINDICES_H
