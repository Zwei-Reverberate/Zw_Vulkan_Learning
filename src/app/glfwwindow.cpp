#include "glfwwindow.h"
#include "../enum/appenum.h"

GlfwWdindow::GlfwWdindow()
{
	m_window = nullptr;
}

void GlfwWdindow::initWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	//glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // 设置 glfw 窗口大小是否可调整
	m_window = glfwCreateWindow(appenum::GLFWWINDOW_WIDTH, 
								appenum::GLFWWINDOW_HEIGHT, 
								appenum::GLFWWINDOW_NAME, 
								nullptr, nullptr);
	glfwSetWindowUserPointer(m_window, this);
	glfwSetFramebufferSizeCallback(m_window, framebufferResizeCallback);
}

void GlfwWdindow::destroyWindow()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

GLFWwindow* GlfwWdindow::getWindow() const
{
	return m_window;
}

bool GlfwWdindow::getIsFramebufferResized() const
{
	return m_framebufferResized;
}

void GlfwWdindow::setIsFramebufferResized(bool isResized)
{
	m_framebufferResized = isResized;
}

void GlfwWdindow::framebufferResizeCallback(GLFWwindow* window, int width, int height)
{
	auto app = reinterpret_cast<GlfwWdindow*>(glfwGetWindowUserPointer(window));
	app->setIsFramebufferResized(true);
}
