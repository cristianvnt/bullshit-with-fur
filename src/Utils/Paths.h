#pragma once
#include <filesystem>

inline const std::filesystem::path ASSETS_DIRECTORY = ASSETS_DIR;

inline std::filesystem::path ShaderPath(const std::string& name, const std::string& extension)
{
	return ASSETS_DIRECTORY / "shaders" / (name + extension);
}
