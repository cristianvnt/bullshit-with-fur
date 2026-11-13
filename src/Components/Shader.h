#pragma once

#include "glm/glm.hpp"

#include "Utils/Logger.h"

#include <string>
#include <unordered_map>
#include <filesystem>

class Shader
{
private:
	unsigned int _shaderProgram;
	std::unordered_map<std::string, int> _uniformLocationCache;
	std::filesystem::path _vertexPath;
	std::filesystem::path _fragmentPath;

	std::filesystem::file_time_type _vertexTimestamp;
	std::filesystem::file_time_type _fragmentTimestamp;
	float _timeSinceLastCheck = 0.f;

public:
	Shader() = default;
	Shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);
	~Shader();

	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;

	Shader(Shader&& other) noexcept
		: _shaderProgram(other._shaderProgram),
		_uniformLocationCache(std::move(other._uniformLocationCache)),
		_vertexPath(std::move(other._vertexPath)),
		_fragmentPath(std::move(other._fragmentPath)),
		_vertexTimestamp(other._vertexTimestamp),
		_fragmentTimestamp(other._fragmentTimestamp),
		_timeSinceLastCheck(other._timeSinceLastCheck)
	{
		other._shaderProgram = 0;
	}

	Shader& operator=(Shader&& other) noexcept
	{
		if (this != &other)
		{
			glDeleteProgram(_shaderProgram);

			_shaderProgram = other._shaderProgram;
			_uniformLocationCache = std::move(other._uniformLocationCache);
			_vertexPath = std::move(other._vertexPath);
			_fragmentPath = std::move(other._fragmentPath);
			_vertexTimestamp = other._vertexTimestamp;
			_fragmentTimestamp = other._fragmentTimestamp;
			_timeSinceLastCheck = other._timeSinceLastCheck;

			other._shaderProgram = 0;
		}
		return *this;
	}

	void ReloadChanges(float dt);

	void Bind() const;
	void Unbind() const;

	int GetUniformLocation(const std::string& name);

	void SetUniform1i(const std::string& name, int value);
	void SetUniformVec4(const std::string& name, const glm::vec4& value);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int LoadProgram();

	// HOT RELOAD
	void Reload();
	bool NeedsReload() const;
};
