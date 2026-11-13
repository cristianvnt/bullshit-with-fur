#pragma once

#include <glad/glad.h>

#include "Utils/Logger.h"

#include <vector>

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:
			return sizeof(GLfloat);
		case GL_UNSIGNED_INT:
			return sizeof(GLuint);
		case GL_UNSIGNED_BYTE:
			return sizeof(GLubyte);
		}

		GL_ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> _elements{};
	unsigned int _stride{};

public:
	VertexBufferLayout() = default;
	~VertexBufferLayout() = default;

	template<typename T>
	VertexBufferLayout& Push(unsigned int count)
	{
		if constexpr (std::is_same_v<T, float>)
		{
			_elements.push_back({ GL_FLOAT, count, GL_FALSE });
			_stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
		}
		else if constexpr (std::is_same_v<T, unsigned int>)
		{
			_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
			_stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
		}
		else if constexpr (std::is_same_v<T, unsigned char>)
		{
			_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
			_stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
		}
		else
		{
			static_assert(sizeof(T) == 0, "Unsuported type for VertexBufferLayout::Push\n");
		}

		return *this;
	}

	const std::vector<VertexBufferElement>& GetElements() const { return _elements; }
	unsigned int GetStride() const { return _stride; }
};
