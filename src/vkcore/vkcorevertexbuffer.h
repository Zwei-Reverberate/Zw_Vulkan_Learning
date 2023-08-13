#ifndef VKCOREVERTEXBUFFER_H
#define VKCOREVERTEXBUFFER_H
#include "vkcorelogicaldevice.h"
#include "vkcorephysicaldevice.h"
#include "../geometry/zwvertex.h"

class VkcoreVertexBuffer
{
public:
	VkcoreVertexBuffer() = default;
	~VkcoreVertexBuffer() = default;
	void create(std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice, const std::vector<ZwVertex>& zwVertices, std::shared_ptr<VkcorePhysicalDevice> pPhysicalDevice);
	void destroy(std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice);
	static uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties, std::shared_ptr<VkcorePhysicalDevice> pPhysicalDevice);
	VkBuffer getVertexBuffer();
	int getVertexSize() const;
private:
	VkBuffer m_vertexBuffer;
	VkDeviceMemory m_vertexBufferMemory;
	int m_vertexSize = 0;
};

#endif // !VKCOREVERTEXBUFFER

