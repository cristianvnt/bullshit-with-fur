#pragma once

class IndexBuffer
{
private:
	unsigned int _ebo;
	unsigned int _count;

public:
	IndexBuffer(const void* data, unsigned int count);
	~IndexBuffer();

	IndexBuffer(const IndexBuffer&) = delete;
	IndexBuffer& operator=(const IndexBuffer&) = delete;
	IndexBuffer(IndexBuffer&&) = delete;
	IndexBuffer& operator=(IndexBuffer&&) = delete;

	void Bind() const;
	void Unbind() const;

	unsigned int GetCount() const { return _count; }
};
