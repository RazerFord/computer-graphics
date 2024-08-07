#include "VertexBuffer.hpp"

namespace render
{
VertexBuffer::VertexBuffer()
	: _id(0)
{}

VertexBuffer::VertexBuffer(VertexBuffer && vertexBuffer) noexcept
	: _id(vertexBuffer._id)
{
	vertexBuffer._id = 0;
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &_id);
}

VertexBuffer & VertexBuffer::operator=(VertexBuffer && vertexBuffer) noexcept
{
	if (this == &vertexBuffer)
	{
		return vertexBuffer;
	}

	_id = vertexBuffer._id;
	vertexBuffer._id = 0;

	return *this;
}

void VertexBuffer::init(const void * data, const size_t size)
{
	glCreateBuffers(1, &_id);
	glBindBuffer(GL_ARRAY_BUFFER, _id);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::update(const void * data, const size_t size) const
{
	glBindBuffer(GL_ARRAY_BUFFER, _id);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, _id);
}

void VertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
}// namespace render