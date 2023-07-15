#ifndef VKCORESYNCHRONIZATION_H
#define VKCORESYNCHRONIZATION_H
#include "../vkcore/vkcorelogicaldevice.h"
#include <vector>

class VkcoreSynchronization
{
private:
	std::vector<VkSemaphore> m_imageAvailableSemaphores; // ��ʶ��׼������Ⱦ
	std::vector<VkSemaphore> m_renderFinishedSemaphores; // ��ʶ��Ⱦ�����
	std::vector<VkFence> m_inFlightFences; // ȷ��ÿ��ֻ��Ⱦһ֡

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
