#ifndef QUEUEFAMILYINDICES_H
#define QUEUEFAMILYINDICES_H
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <optional>
#include <memory>
#include "../vkcore/vkcoresurface.h"

struct QueueFamilyIndices
{
    std::optional<uint32_t> m_graphicsFamily;
    std::optional<uint32_t> m_presentFamily;

    bool isComplete();

    // 查找所需的 queue families
    static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, std::shared_ptr<VkcoreSurface>);
};
#endif // !QUEUEFAMILYINDICES_H
