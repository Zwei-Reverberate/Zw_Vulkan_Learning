#ifndef VKSHADER_H
#define VKSHADER_H
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include "../vkcore/vkcorelogicaldevice.h"

enum class ShaderType
{
	VERTEX  = 0,
	FRAGMENT,
};

class VkShader
{
private:
	VkShaderModule m_shaderModule;
	VkPipelineShaderStageCreateInfo m_shaderStageInfo;

public:
	VkShader() = default;
	~VkShader() = default;
	static std::vector<char> readFile(const std::string& filename);
	void create(const std::string& filename, std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice, ShaderType type);
	void createShaderModule(const std::vector<char>& code, std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice);
	VkPipelineShaderStageCreateInfo getShaderStageInfo();
	void destroy(std::shared_ptr<VkcoreLogicalDevice> pLogicalDevice);
};

#endif // !VKSHADER_H

