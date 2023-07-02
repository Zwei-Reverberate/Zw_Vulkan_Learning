#ifndef VKCORESYNCHRONIZATION_H
#define VKCORESYNCHRONIZATION_H
#include "../vkcore/vkcorelogicaldevice.h"

class VkcoreSynchronization
{
private:
	VkSemaphore m_imageAvailableSemaphore; // ��ʶ��׼������Ⱦ
	VkSemaphore m_renderFinishedSemaphore; // ��ʶ��Ⱦ�����
	VkFence m_inFlightFence; // ȷ��ÿ��ֻ��Ⱦһ֡

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
