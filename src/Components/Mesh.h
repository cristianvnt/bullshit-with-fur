#pragma once

#include "Buffers/VertexArray.h"
#include "Buffers/IndexBuffer.h"

struct Mesh
{
	VertexArray* vao{};
	IndexBuffer* ibo{};
	unsigned int vertexCount{};
};