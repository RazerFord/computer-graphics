#include "VertexArray.hpp"
#include "VertexBuffer.hpp"

namespace render
{
VertexArray::VertexArray()
	: _id(0)
	, _countSavedBuffers(0)
{
	glGenVertexArrays(1, &_id);
}

VertexArray::VertexArray(VertexArray && vertexArray) noexcept
	: _id(vertexArray._id)
	, _countSavedBuffers(vertexArray._countSavedBuffers)
{
	vertexArray._id = 0;
	vertexArray._countSavedBuffers = 0;
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &_id);
}

VertexArray & VertexArray::operator=(VertexArray && vertexArray) noexcept
{
	if (this == &vertexArray)
	{
		return vertexArray;
	}

	_id = vertexArray._id;
	_countSavedBuffers = vertexArray._countSavedBuffers;
	vertexArray._id = 0;
	vertexArray._countSavedBuffers = 0;

	return *this;
}

void VertexArray::addBuffer(const VertexBuffer & vertexBuffer, const VertexBufferLayout & vertexBufferLayout)
{
	bind();
	vertexBuffer.bind();
	const auto & layouts = vertexBufferLayout.layouts();
	GLbyte * offset = 0;
	for (GLuint i = 0; i < layouts.size(); i++)
	{
		const auto [count, type, normalized, size] = layouts[i];
		GLuint currentAttribIndex = i + _countSavedBuffers;
		glVertexAttribPointer(currentAttribIndex, count, type, normalized, vertexBufferLayout.stride(), offset);
		glEnableVertexAttribArray(currentAttribIndex);
		offset = offset + size;
	}
	_countSavedBuffers += layouts.size();
	vertexBuffer.unbind();
	unbind();
}

void VertexArray::bind() const
{
	glBindVertexArray(_id);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}
}// namespace render