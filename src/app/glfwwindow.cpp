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
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	m_window = glfwCreateWindow(appenum::GLFWWINDOW_WIDTH, 
								appenum::GLFWWINDOW_HEIGHT, 
								appenum::GLFWWINDOW_NAME, 
								nullptr, nullptr);
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
