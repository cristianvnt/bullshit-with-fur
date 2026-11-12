#include "Settings.h"
#include <toml++/toml.hpp>

Settings LoadSettings(const std::filesystem::path& file)
{
	Settings settings;

	try
	{
		toml::table table = toml::parse_file(file.string());
		settings.window.title = table["window"]["title"].value_or(settings.window.title);
		settings.window.width = table["window"]["width"].value_or(settings.window.width);
		settings.window.height = table["window"]["height"].value_or(settings.window.height);
		settings.window.vsync = table["window"]["vsync"].value_or(settings.window.vsync);
		settings.fov = table["fov"].value_or(settings.fov);
	}
	catch (const toml::parse_error)
	{
	}

	return settings;
}
