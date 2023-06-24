#ifndef VKCOREGRAPHICSPIPELINE_H
#define VKCOREGRAPHICSPIPELINE_H
#include "../graphicspipeline/vkshader.h"
#include <memory>

class VkcoreGraphicsPipeline
{
private:
	VkPipelineLayout m_pipelineLayout;

public:
	VkcoreGraphicsPipeline() = default;
	~VkcoreGraphicsPipeline() = default;
	void create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice);
	void destroy(std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice);
};

#endif // !VKCOREGRAPHICSPIPELINE_H

