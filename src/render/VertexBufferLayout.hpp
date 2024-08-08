#pragma once

#include <glad/glad.h>
#include <vector>

namespace render
{
class VertexBufferLayout
{
public:
	struct Layout {
		GLuint count;
		GLenum type;
		GLboolean normalized;
		GLuint size;

		Layout(const GLuint count,
			   const GLenum type,
			   const GLboolean normalized,
			   const GLuint size)
			: count(count)
			, type(type)
			, normalized(normalized)
			, size(size)
		{}
	};

private:
	std::vector<Layout> _layouts;
	GLuint _stride;

public:
	VertexBufferLayout();

	void addElementLayoutFloat(const GLuint count, const GLboolean normalized);

	GLuint stride() const;
	const std::vector<Layout> & layouts() const;
};
}// namespace render