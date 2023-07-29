#ifndef GLFWWINDOW_H
#define GLFWWINDOW_H
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class GlfwWdindow
{
private:
	GLFWwindow* m_window;
	bool m_framebufferResized = false;

public:
	GlfwWdindow();
	~GlfwWdindow() = default;
	void initWindow();
	void destroyWindow();
	GLFWwindow* getWindow() const;
	bool getIsFramebufferResized() const;
	void setIsFramebufferResized(bool isResized);
	static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
};

#endif // !GLFWWINDOW_H
