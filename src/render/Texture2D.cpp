#include "Texture2D.hpp"
#include <stdexcept>

namespace
{
inline const render::Texture2D::SubTexture2D defaultSubTexture;
}

namespace render
{
GLenum selectMode(const int channels)
{
	switch (channels)
	{
		case 1: {
			return GL_RED;
		}
		case 2: {
			return GL_RG;
		}
		case 3: {
			return GL_RGB;
		}
		case 4: {
			return GL_RGBA;
		}
		default: {
			throw std::runtime_error("wrong number of channels");
		}
	}
}

Texture2D::Texture2D(
	const int width,
	const int height,
	const stbi_uc * data,
	const int channels,
	const GLenum filter,
	const GLenum wrapMode)
	: _width(width)
	, _height(height)
{
	_mode = selectMode(channels);

	glGenTextures(1, &_textureID);

	glBindTexture(GL_TEXTURE_2D, _textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

	glTexImage2D(GL_TEXTURE_2D, 0, _mode, _width, _height, 0, _mode, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2D::Texture2D(Texture2D && texture2D)
	: _width(texture2D._width)
	, _height(texture2D._height)
{
	_textureID = texture2D._textureID;
	_mode = texture2D._mode;

	texture2D._textureID = 0;
}

Texture2D & Texture2D::operator=(Texture2D && texture2D) noexcept
{
	if (this == &texture2D)
	{
		return *this;
	}
	_textureID = texture2D._textureID;
	_width = texture2D._width;
	_height = texture2D._height;
	_mode = texture2D._mode;

	texture2D._textureID = 0;

	return *this;
}

void Texture2D::addSubTexture(const std::string & name, const glm::vec2 & leftBottomUV, const glm::vec2 & rightTopUV)
{
	_subTextures.emplace(name, Texture2D::SubTexture2D(leftBottomUV, rightTopUV));
}

const Texture2D::SubTexture2D & Texture2D::getSubTexture(const std::string & name) const
{
	if (auto it = _subTextures.find(name); it != _subTextures.end())
	{
		return it->second;
	}

	return defaultSubTexture;
}

int Texture2D::width() const
{
	return _width;
}

int Texture2D::height() const
{
	return _height;
}

void Texture2D::bind() const
{
	glBindTexture(GL_TEXTURE_2D, _textureID);
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &_textureID);
}
}// namespace render