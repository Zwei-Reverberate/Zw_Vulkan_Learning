#ifndef ZWVERTEX_H
#define ZWVERTEX_H
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <array>

struct ZwVertex
{
	glm::vec3 pos;
	glm::vec3 color;
};

const std::vector<ZwVertex> zwVertices = 
{
    {{0.0f, -0.5f, 0.0f}, {1.0f, 1.0f, 0.0f}},
    {{0.5f, 0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},
    {{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}}
};

class verUtil
{
public:
    static VkVertexInputBindingDescription getBindingDescription();
    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions(); // 现在只有位置和颜色两个属性
};

#endif // !ZWVERTEX_H

