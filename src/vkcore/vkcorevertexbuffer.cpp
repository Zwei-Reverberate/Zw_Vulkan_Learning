#include "vkcorevertexbuffer.h"
#include <stdexcept>

void VkcoreVertexBuffer::create(std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice, const std::vector<ZwVertex>& zwVertices, std::shared_ptr<VkcorePhysicalDevice> pPhysicalDevice)
{
	if (!pLogicalDevice || !pPhysicalDevice)
		return;

    m_vertexSize = zwVertices.size();

    // 创建 vertex buffer
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = sizeof(zwVertices[0]) * zwVertices.size();
    bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    if (vkCreateBuffer(pLogicalDevice->getDevice(), &bufferInfo, nullptr, &m_vertexBuffer) != VK_SUCCESS)
        throw std::runtime_error("failed to create vertex buffer!");
    
    // 申请内存
    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(pLogicalDevice->getDevice(), m_vertexBuffer, &memRequirements);

    // 分配内存
    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, pPhysicalDevice);
    if (vkAllocateMemory(pLogicalDevice->getDevice(), &allocInfo, nullptr, &m_vertexBufferMemory) != VK_SUCCESS)
        throw std::runtime_error("failed to allocate vertex buffer memory!");

    // 关联内存与 vetex buffer
    vkBindBufferMemory(pLogicalDevice->getDevice(), m_vertexBuffer, m_vertexBufferMemory, 0);

    // 将顶点数据复制到 buffer 中
    void* data;
    vkMapMemory(pLogicalDevice->getDevice(), m_vertexBufferMemory, 0, bufferInfo.size, 0, &data);
    std::memcpy(data, zwVertices.data(), (size_t)bufferInfo.size);
    vkUnmapMemory(pLogicalDevice->getDevice(), m_vertexBufferMemory);
}

void VkcoreVertexBuffer::destroy(std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice)
{
	if (!pLogicalDevice)
		return;
	vkDestroyBuffer(pLogicalDevice->getDevice(), m_vertexBuffer, nullptr);
    vkFreeMemory(pLogicalDevice->getDevice(), m_vertexBufferMemory, nullptr);
}

uint32_t VkcoreVertexBuffer::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties, std::shared_ptr<VkcorePhysicalDevice> pPhysicalDevice)
{
    if (!pPhysicalDevice)
        return uint32_t();
    VkPhysicalDeviceMemoryProperties memProperties; // 查询可用的内存类型信息
    vkGetPhysicalDeviceMemoryProperties(pPhysicalDevice->getPhysicalDevice(), &memProperties);
    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) 
    {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
            return i;
    }
    throw std::runtime_error("failed to find suitable memory type!");
}

VkBuffer VkcoreVertexBuffer::getVertexBuffer()
{
    return m_vertexBuffer;
}

int VkcoreVertexBuffer::getVertexSize() const
{
    return m_vertexSize;
}
