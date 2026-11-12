#pragma once

#include "Utils/Settings.h"

struct GLFWwindow;

class Window
{
private:
	GLFWwindow* _window = nullptr;

public:
	Window() = default;
	~Window();

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator=(Window&&) = delete;

	bool Init(const WindowsSettings& settings);
	void SwapBuffers();
	void PollEvents();
	bool ShouldClose() const;

	GLFWwindow* GetGLFWwindow() const { return _window; }
};
