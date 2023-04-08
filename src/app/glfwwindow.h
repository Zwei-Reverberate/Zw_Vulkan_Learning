#ifndef GLFWWINDOW_H
#define GLFWWINDOW_H
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class GlfwWdindow
{
private:
	GLFWwindow* m_window;

public:
	GlfwWdindow();
	~GlfwWdindow() = default;
	void initWindow();
	void destroyWindow();
	GLFWwindow* getWindow() const;
};

#endif // !GLFWWINDOW_H
