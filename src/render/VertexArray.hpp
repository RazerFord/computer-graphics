#pragma once

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include <glad/glad.h>

namespace render
{
class VertexArray
{
private:
	GLuint _id;
	GLuint _countSavedBuffers;

public:
	VertexArray();
	VertexArray(VertexArray && vertexArray) noexcept;
	~VertexArray();

	VertexArray & operator=(VertexArray && vertexArray) noexcept;

	void addBuffer(const VertexBuffer & vertexBuffer, const VertexBufferLayout & vertexBufferLayout);
	void bind() const;
	void unbind() const;
};
}// namespace render