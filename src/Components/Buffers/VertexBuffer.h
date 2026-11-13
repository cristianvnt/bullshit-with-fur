#pragma once

class VertexBuffer
{
private:
	unsigned int _vbo;
	unsigned int _size;

public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	VertexBuffer(const VertexBuffer&) = delete;
	VertexBuffer& operator=(const VertexBuffer&) = delete;
	VertexBuffer(VertexBuffer&&) = delete;
	VertexBuffer& operator=(VertexBuffer&&) = delete;

	void Bind() const;
	void Unbind() const;

	unsigned int GetSize() const { return _size; }
};
