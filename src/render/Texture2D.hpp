#pragma once

#include "../resources/stb_image.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <map>
#include <string>

namespace render
{
class Texture2D
{
public:
	struct SubTexture2D {
		glm::vec2 leftBottomUV;
		glm::vec2 rightTopUV;

		SubTexture2D(const glm::vec2 & leftBottomUV, const glm::vec2 & rightTopUV)
			: leftBottomUV(leftBottomUV)
			, rightTopUV(rightTopUV)
		{}

		SubTexture2D()
			: leftBottomUV(0.0F)
			, rightTopUV(1.0F)
		{}
	};

private:
	GLuint _textureID = 0;
	int _width;
	int _height;
	GLenum _mode;
	std::map<std::string, SubTexture2D> _subTextures;

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

	void addSubTexture(const std::string & name, const glm::vec2 & leftBottomUV, const glm::vec2 & rightTopUV);
	const SubTexture2D & getSubTexture(const std::string & name) const;

	int width() const;
	int height() const;

	void bind() const;

	~Texture2D();
};
}// namespace render