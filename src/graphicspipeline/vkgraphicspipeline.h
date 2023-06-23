#ifndef VKGRAPHICSPIPELINE_H
#define VKGRAPHICSPIPELINE_H
#include "../graphicspipeline/vkshader.h"
#include <memory>

class VkGraphicsPipeline
{
private:
	VkPipelineLayout m_pipelineLayout;

public:
	VkGraphicsPipeline() = default;
	~VkGraphicsPipeline() = default;
	void create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice);
	void destroy(std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice);
};

#endif // !VKCOREGRAPHICSPIPELINE_H

