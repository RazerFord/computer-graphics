#pragma once

#include <cstddef>
#include <glad/glad.h>

namespace render
{
class VertexBuffer
{
private:
	GLuint _id;

public:
	VertexBuffer();
	VertexBuffer(VertexBuffer && vertexBuffer) noexcept;
	~VertexBuffer();

	VertexBuffer & operator=(VertexBuffer && vertexBuffer) noexcept;

	void init(const void * data, const size_t size);
	void update(const void * data, const size_t size) const;
	void bind() const;
	void unbind() const;
};
}// namespace render