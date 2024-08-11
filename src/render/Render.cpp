#include "Render.hpp"
#include "IndexBuffer.hpp"
#include <GL/gl.h>

namespace render
{
void Render::draw(const VertexArray & vertexArray, const IndexBuffer & indexBuffer, const ShaderProgram & shaderProgram)
{
	shaderProgram.use();
	vertexArray.bind();

	glDrawElements(GL_TRIANGLES, indexBuffer.count(), GL_UNSIGNED_INT, nullptr);

	vertexArray.unbind();
}

void Render::enable(const GLenum cap)
{
	glEnable(cap);
}

void Render::disable(const GLenum cap)
{
	glDisable(cap);
}

void Render::setClearColor(const float r, const float g, const float b, const float a)
{
	glClearColor(r, g, b, a);
}

void Render::clear(const GLbitfield bitfield)
{
	glClear(bitfield);
}

void Render::setViewport(const GLuint width, const GLuint height, const GLuint leftOffset, const GLuint bottomOffset)
{
	glViewport(leftOffset, bottomOffset, width, height);
}

std::string Render::getRenderer()
{
	return std::string(reinterpret_cast<char *>(const_cast<GLubyte *>(glGetString(GL_RENDERER))));
}

std::string Render::getVersion()
{
	return std::string(reinterpret_cast<char *>(const_cast<GLubyte *>(glGetString(GL_VERSION))));
}
}// namespace render
