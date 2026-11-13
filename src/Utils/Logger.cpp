#include "Logger.h"

#include <iostream>
#include <vector>
#include <string>

namespace
{
	const char* GetGLErrorString(GLenum err)
	{
		switch (err)
		{
		case GL_INVALID_ENUM:
			return "INVALID_ENUM";
		case GL_INVALID_VALUE:
			return "INVALID_VALUE";
		case GL_INVALID_OPERATION:
			return "INVALID_OPERATION";
		case GL_STACK_UNDERFLOW:
			return "STACK_UNDERFLOW";
		case GL_STACK_OVERFLOW:
			return "STACK_OVERFLOW";
		case GL_OUT_OF_MEMORY:
			return "OUT_OF_MEMORY";
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			return "INVALID_FRAMEBUFFER_OPERATION";
		default:
			return "UNKNOWN_GL_ERROR";
		}
	}
}

bool GLLog::LogShader(unsigned int shader)
{
	int success;
	GL_CHECK(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
	if (success)
		return true;

	int length = 0;
	GL_CHECK(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length));

	std::string infoLog(length, '\0');
	int written = 0;
	GL_CHECK(glGetShaderInfoLog(shader, length, &written, infoLog.data()));
	infoLog.resize(written);

	int type;
	GL_CHECK(glGetShaderiv(shader, GL_SHADER_TYPE, &type));
	const char* typeStr = [&]()
		{
			switch (type)
			{
			case GL_VERTEX_SHADER:
				return "VERTEX";
			case GL_FRAGMENT_SHADER:
				return "FRAGMENT";
			default:
				return "UNKNOWN";
			}
		}();

	std::cerr << "ERROR::SHADER:: -> " << typeStr << " <- ::COMPILATION_FAILED\n" << infoLog << "\n";
	return false;
}

bool GLLog::LogProgram(unsigned int program)
{
	int success;
	GL_CHECK(glGetProgramiv(program, GL_LINK_STATUS, &success));
	if (success)
		return true;

	int length = 0;
	GL_CHECK(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length));

	std::string infoLog(length, '\0');
	int written = 0;
	GL_CHECK(glGetProgramInfoLog(program, length, &written, infoLog.data()));
	infoLog.resize(written);

	std::cerr << "ERROR::PROGRAM::LINKING_FAILED ->\n" << infoLog << " <- \n";
	return false;
}

void GLError::ClearError()
{
	while (glGetError() != GL_NO_ERROR) {}
}

bool GLError::CheckError_(const char* func, const char* file, int line)
{
	std::vector<GLenum> errors;
	while (GLenum err = glGetError())
		errors.push_back(err);

	for (GLenum err : errors)
		std::cerr << "[OpenGL] " << GetGLErrorString(err) << " | " << func << "\n | " << file << " (" << line << ")\n";

	return errors.empty();
}
