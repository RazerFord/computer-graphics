#pragma once

#include "../resources/stb_image.h"
#include <glad/glad.h>

namespace render
{
class Texture2D
{
private:
	GLuint _textureID = 0;
	int _width;
	int _height;
	GLenum _mode;

public:
	Texture2D(
		const int width,
		const int height,
		const stbi_uc * data,
		const int channels = 4,
		const GLenum filter = GL_LINEAR,
		const GLenum wrapMode = GL_CLAMP_TO_EDGE);

	Texture2D(Texture2D && texture2D);

	Texture2D & operator=(Texture2D && texture2D) noexcept;

    void bind() const;

	~Texture2D();
};
}// namespace render