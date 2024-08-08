#pragma once

#include <cstddef>
#include <glad/glad.h>

namespace render
{
class IndexBuffer
{
private:
	GLuint _id;
	GLuint _count;

public:
	IndexBuffer();
	IndexBuffer(IndexBuffer && indexBuffer) noexcept;
	~IndexBuffer();

	IndexBuffer & operator=(IndexBuffer && indexBuffer) noexcept;

	void init(const void * data, const size_t count);
	void bind() const;
	void unbind() const;

	GLuint count() const;
};
}// namespace render