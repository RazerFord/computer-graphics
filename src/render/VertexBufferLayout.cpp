#include "VertexBufferLayout.hpp"

namespace render
{
VertexBufferLayout::VertexBufferLayout()
	: _stride(0)
{}

void VertexBufferLayout::addElementLayoutFloat(const GLuint count, const GLboolean normalized)
{
	_layouts.emplace_back(count, GL_FLOAT, normalized, count * sizeof(GLfloat));
	_stride += count * sizeof(GLfloat);
}

GLuint VertexBufferLayout::stride() const
{
	return _stride;
}

const std::vector<VertexBufferLayout::Layout> & VertexBufferLayout::layouts() const
{
	return _layouts;
}
}// namespace render