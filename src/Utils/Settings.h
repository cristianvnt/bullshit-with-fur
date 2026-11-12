#pragma once

#include <filesystem>

struct WindowsSettings
{
	const char* title = "Bullshit With Fur";
	int width = 1280;
	int height = 720;
	bool fullscreen = false;
	bool vsync = true;
};

struct Settings
{
	WindowsSettings window;
	float fov = 70.f;
};

Settings LoadSettings(const std::filesystem::path& file);
