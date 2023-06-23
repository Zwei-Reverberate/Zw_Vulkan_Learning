#ifndef VKGRAPHICSPIPELINE_H
#define VKGRAPHICSPIPELINE_H
#include "../graphicspipeline/vkshader.h"
#include <memory>

class VkGraphicsPipeline
{
private:
	std::shared_ptr<VkShader> m_vertexShader;
	std::shared_ptr<VkShader> m_fragmentSahder;

public:
	VkGraphicsPipeline() = default;
	~VkGraphicsPipeline() = default;
	void create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice);
};

#endif // !VKCOREGRAPHICSPIPELINE_H

