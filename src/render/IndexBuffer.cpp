#include "IndexBuffer.hpp"

namespace render
{
IndexBuffer::IndexBuffer()
	: _id(0)
{}

IndexBuffer::IndexBuffer(IndexBuffer && indexBuffer) noexcept
	: _id(indexBuffer._id)
{
	indexBuffer._id = 0;
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &_id);
}

IndexBuffer & IndexBuffer::operator=(IndexBuffer && indexBuffer) noexcept
{
	if (this == &indexBuffer)
	{
		return indexBuffer;
	}

	_id = indexBuffer._id;
	indexBuffer._id = 0;

	return *this;
}

void IndexBuffer::init(const void * data, const size_t size)
{
	glCreateBuffers(1, &_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
}

void IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
}// namespace render