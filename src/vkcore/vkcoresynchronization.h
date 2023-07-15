#ifndef VKCORESYNCHRONIZATION_H
#define VKCORESYNCHRONIZATION_H
#include "../vkcore/vkcorelogicaldevice.h"
#include <vector>

class VkcoreSynchronization
{
private:
	std::vector<VkSemaphore> m_imageAvailableSemaphores; // 标识已准备好渲染
	std::vector<VkSemaphore> m_renderFinishedSemaphores; // 标识渲染已完成
	std::vector<VkFence> m_inFlightFences; // 确保每次只渲染一帧

public:
	VkcoreSynchronization() = default;
	~VkcoreSynchronization() = default;
	void create(std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice);
	void destroy(std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice);

	std::vector<VkFence>& getInFlightFences();
	std::vector<VkSemaphore> getImageAvailableSemaphores();
	std::vector<VkSemaphore> getRenderFinishedSemaphores();
};

#endif // !VKCORESYNCHRONIZATION_H
