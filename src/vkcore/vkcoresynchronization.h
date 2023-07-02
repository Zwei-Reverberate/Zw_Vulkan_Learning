#ifndef VKCORESYNCHRONIZATION_H
#define VKCORESYNCHRONIZATION_H
#include "../vkcore/vkcorelogicaldevice.h"

class VkcoreSynchronization
{
private:
	VkSemaphore m_imageAvailableSemaphore; // 标识已准备好渲染
	VkSemaphore m_renderFinishedSemaphore; // 标识渲染已完成
	VkFence m_inFlightFence; // 确保每次只渲染一帧

public:
	VkcoreSynchronization() = default;
	~VkcoreSynchronization() = default;
	void create(std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice);
	void destroy(std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice);

	VkFence& getInFlightFence();
	VkSemaphore getImageAvailableSemaphore();
	VkSemaphore getRenderFinishedSemaphore();
};

#endif // !VKCORESYNCHRONIZATION_H
