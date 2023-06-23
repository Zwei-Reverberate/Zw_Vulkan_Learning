#include "vkgraphicspipeline.h"

void VkGraphicsPipeline::create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice)
{
	if (!pLogicalDevice)
	{
		return;
	}

	m_vertexShader = std::make_shared<VkShader>();
	m_fragmentSahder = std::make_shared<VkShader>();
	m_vertexShader->create(vertexShaderPath, pLogicalDevice, ShaderType::VERTEX);
	m_fragmentSahder->create(fragmentShaderPath, pLogicalDevice, ShaderType::FRAGMENT);
	VkPipelineShaderStageCreateInfo shaderStages[] = {m_vertexShader->getShaderStageInfo(), m_fragmentSahder->getShaderStageInfo()};
	m_vertexShader->destroy(pLogicalDevice);
	m_fragmentSahder->destroy(pLogicalDevice);
}
