#ifndef APPENUM_H
#define APPENUM_H
#include <string>
#include <vector>

// ��ͷ�ļ���ֻ�����������壬��ֹ�ض������
namespace appenum
{
	extern const int GLFWWINDOW_WIDTH;
	extern const int GLFWWINDOW_HEIGHT;
	extern const char* GLFWWINDOW_NAME;

	extern const char* APPLICATION_NAME;
	extern const char* ENGINE_NAME;

	extern const std::vector<const char*> validationLayers;

	extern const std::vector<const char*> deviceExtensions;

	extern const bool enableValidationLayers;
}

#endif