#pragma once

class VertexBuffer;
class VertexBufferLayout;

class VertexArray
{
private:
	unsigned int _vao;

public:
	VertexArray();
	~VertexArray();

	VertexArray(const VertexArray&) = delete;
	VertexArray& operator=(const VertexArray&) = delete;
	VertexArray(VertexArray&&) = delete;
	VertexArray& operator=(VertexArray&&) = delete;

	void Bind() const;
	void Unbind() const;

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) const;
};
