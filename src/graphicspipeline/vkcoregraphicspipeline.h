#ifndef VKCOREGRAPHICSPIPELINE_H
#define VKCOREGRAPHICSPIPELINE_H
#include "../graphicspipeline/vkshader.h"
#include "../graphicspipeline/vkcorerenderpass.h"
#include "../geometry/zwvertex.h"
#include <memory>

class VkcoreGraphicsPipeline
{
private:
	VkPipelineLayout m_pipelineLayout;
	VkPipeline m_graphicsPipeline;

public:
	VkcoreGraphicsPipeline() = default;
	~VkcoreGraphicsPipeline() = default;
	void create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice, std::shared_ptr<VkcoreRenderPass> pRenderPass);
	void destroy(std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice);
	VkPipeline getGraphicsPipeline();
};

#endif // !VKCOREGRAPHICSPIPELINE_H

