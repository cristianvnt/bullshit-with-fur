#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Utils/Logger.h"

Window::~Window()
{
	if (_window)
		glfwDestroyWindow(_window);

	glfwTerminate();
}

static void FramebufferSizeCallback(GLFWwindow* /*window*/, int width, int height)
{
	GL_CHECK(glViewport(0, 0, width, height));
}

static void GlfwErrorCallback(int code, const char* desc)
{
	std::cerr << "[GLFW " << code << "] " << desc << "\n";
}

bool Window::Init(const WindowsSettings& settings)
{
	glfwSetErrorCallback(GlfwErrorCallback);

	if (!glfwInit())
	{
		std::cerr << "GLFW failed to init.\n";
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifndef NDEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

	_window = glfwCreateWindow(settings.width, settings.height, settings.title, nullptr, nullptr);
	if (!_window)
	{
		std::cerr << "GLFW window creation failed.\n";
		return false;
	}

	glfwMakeContextCurrent(_window);
	glfwSwapInterval(settings.vsync ? 1 : 0);
	glfwSetFramebufferSizeCallback(_window, FramebufferSizeCallback);

	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
	{
		std::cerr << "GLAD failed to load.\n";
		return false;
	}

	std::cout << "OpenGL " << glGetString(GL_VERSION) << " | " << glGetString(GL_RENDERER) << "\n";
	return true;
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(_window);
}

void Window::PollEvents()
{
	glfwPollEvents();
}

bool Window::ShouldClose() const
{
	return glfwWindowShouldClose(_window);
}

