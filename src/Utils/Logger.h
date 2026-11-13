#pragma once

#include <glad/glad.h>

namespace GLLog
{
	bool LogShader(unsigned int shader);
	bool LogProgram(unsigned int program);
}

namespace GLError
{
	void ClearError();
	bool CheckError_(const char* func, const char* file, int line);
}

#define GL_ASSERT(x) \
	do { \
		if (!(x)) \
			__debugbreak(); \
	} while (false)

#ifndef NDEBUG
#define GL_CHECK(x) \
	do { \
		GLError::ClearError(); \
		x; \
		GL_ASSERT(GLError::CheckError_(#x, __FILE__, __LINE__)); \
	} while (false)
#else
#define GL_CHECK(x) x
#endif
