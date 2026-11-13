#include "VertexArray.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray()
{
	GL_CHECK(glGenVertexArrays(1, &_vao));
}

VertexArray::~VertexArray()
{
	GL_CHECK(glDeleteVertexArrays(1, &_vao));
}

void VertexArray::Bind() const
{
	GL_CHECK(glBindVertexArray(_vao));
}

void VertexArray::Unbind() const
{
	GL_CHECK(glBindVertexArray(0));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) const
{
	GL_CHECK(glBindVertexArray(_vao));
	vb.Bind();

	const std::vector<VertexBufferElement> elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); ++i)
	{
		const VertexBufferElement element = elements[i];
		GL_CHECK(glEnableVertexAttribArray(i));
		GL_CHECK(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), reinterpret_cast<const void*>(offset)));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}
