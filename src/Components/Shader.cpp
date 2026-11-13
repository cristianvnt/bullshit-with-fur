#include "Shader.h"

#include "glm/gtc/type_ptr.hpp"

#include <iostream>
#include <fstream>

namespace
{
	bool ReadFile(const std::filesystem::path& path, std::string& contents)
	{
		std::ifstream file(path);
		if (!file.is_open())
		{
			std::cerr << "Count not open shader file: " << path << "\n";
			return false;
		}

		std::stringstream buffer;
		buffer << file.rdbuf();
		contents = buffer.str();
		return true;
	}
}

Shader::Shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
	: _vertexPath(vertexPath), _fragmentPath(fragmentPath)
{
	_shaderProgram = LoadProgram();
	_vertexTimestamp = std::filesystem::last_write_time(_vertexPath);
	_fragmentTimestamp = std::filesystem::last_write_time(_fragmentPath);
}

Shader::~Shader()
{
	GL_CHECK(glDeleteProgram(_shaderProgram));
}

void Shader::ReloadChanges(float dt)
{
	_timeSinceLastCheck += dt;
	if (_timeSinceLastCheck < 1.f)
		return;

	if (NeedsReload())
	{
		Reload();
		_vertexTimestamp = std::filesystem::last_write_time(_vertexPath);
		_fragmentTimestamp = std::filesystem::last_write_time(_fragmentPath);
		std::cout << "[HOT RELOAD] Reloaded " << _vertexPath << " and " << _fragmentPath << "\n";
	}

	_timeSinceLastCheck = 0.f;
}

void Shader::Bind() const
{
	GL_CHECK(glUseProgram(_shaderProgram));
}

void Shader::Unbind() const
{
	GL_CHECK(glUseProgram(0));
}

int Shader::GetUniformLocation(const std::string& name)
{
	auto it = _uniformLocationCache.find(name);
	if (it != _uniformLocationCache.end())
		return it->second;

	int location;
	GL_CHECK(location = glGetUniformLocation(_shaderProgram, name.c_str()));
	if (location == -1)
	{
		std::cout << "[Shader Warning]: Uniform '" << name << "' doesn't exist.\n";
	}

	_uniformLocationCache[name] = location;
	return location;
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	GL_CHECK(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniformVec4(const std::string& name, const glm::vec4& value)
{
	GL_CHECK(glUniform4fv(GetUniformLocation(name), 1, glm::value_ptr(value)));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	GL_CHECK(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix)));
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int shader = 0;
	GL_CHECK(shader = glCreateShader(type));
	const char* src = source.c_str();
	GL_CHECK(glShaderSource(shader, 1, &src, nullptr));
	GL_CHECK(glCompileShader(shader));

	if (!GLLog::LogShader(shader))
	{
		GL_CHECK(glDeleteShader(shader));
		return 0;
	}

	return shader;
}

unsigned int Shader::CreateShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	if (!vs || !fs)
	{
		if (vs)
			GL_CHECK(glDeleteShader(vs));
		if (fs)
			GL_CHECK(glDeleteShader(fs));
		return 0;
	}

	unsigned int program = 0;
	GL_CHECK(program = glCreateProgram());
	GL_CHECK(glAttachShader(program, vs));
	GL_CHECK(glAttachShader(program, fs));
	GL_CHECK(glLinkProgram(program));
	GL_CHECK(glDeleteShader(vs));
	GL_CHECK(glDeleteShader(fs));

	if (!GLLog::LogProgram(program))
	{
		GL_CHECK(glDeleteProgram(program));
		return 0;
	}

	return program;
}

unsigned int Shader::LoadProgram()
{
	std::string vertexSource;
	std::string fragmentSource;
	if (!ReadFile(_vertexPath, vertexSource) || !ReadFile(_fragmentPath, fragmentSource))
		return 0;

	return CreateShaderProgram(vertexSource, fragmentSource);
}

void Shader::Reload()
{
	unsigned int newProgram = LoadProgram();
	if (!newProgram)
		return;

	glDeleteProgram(_shaderProgram);
	_shaderProgram = newProgram;
	_uniformLocationCache.clear();
	std::cout << "Shader reloaded: " << _vertexPath << " / " << _fragmentPath << "\n";
}

bool Shader::NeedsReload() const
{
	std::error_code ec;
	std::filesystem::file_time_type vertexTime = std::filesystem::last_write_time(_vertexPath, ec);
	if (ec)
		return false;

	std::filesystem::file_time_type fragmentTime = std::filesystem::last_write_time(_fragmentPath, ec);
	if (ec)
		return false;

	return vertexTime != _vertexTimestamp || fragmentTime != _fragmentTimestamp;
}
