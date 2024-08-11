#pragma once

#include "IndexBuffer.hpp"
#include "ShaderProgram.hpp"
#include "VertexArray.hpp"
#include <GL/gl.h>

namespace render
{
class Render
{
public:
	static void draw(const VertexArray & vertexArray, const IndexBuffer & indexBuffer, const ShaderProgram & shaderProgram);
	static void enable(const GLenum cap);
	static void disable(const GLenum cap);
	static void setClearColor(const float r, const float g, const float b, const float a);
	static void clear(const GLbitfield bitfield);
	static void setViewport(const GLuint width, const GLuint height, const GLuint leftOffset = 0, const GLuint bottomOffset = 0);

	static std::string getRenderer();
	static std::string getVersion();
};
}// namespace render
