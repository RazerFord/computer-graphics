#include "ResourceManager.hpp"
#include "../render/ShaderProgram.hpp"
#include "../render/Sprite.hpp"
#include "../render/Texture2D.hpp"
#include <fstream>
#include <ios>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace
{
const char pathSeparator =
#ifdef _WIN32
	'\\';
#else
	'/';
#endif
}// namespace

namespace resources
{
ResourceManager::ResourceManager(const std::string & pathToExecutable)
	: _pathToExecutable(pathToExecutable.substr(0, pathToExecutable.find_last_of("/\\")))
{}

std::shared_ptr<render::ShaderProgram> ResourceManager::loadShader(
	const std::string & shaderName,
	const std::string & vertexShader,
	const std::string & fragmentShader)
{
	std::string vertexShaderSource = readFile(vertexShader);
	if (vertexShaderSource.empty())
	{
		std::cerr << "Error read vertex shader source" << std::endl;
		return nullptr;
	}

	std::string fragmentShaderSource = readFile(fragmentShader);
	if (fragmentShaderSource.empty())
	{
		std::cerr << "Error read fragment shader source" << std::endl;
		return nullptr;
	}

	auto sp = std::make_shared<render::ShaderProgram>(vertexShaderSource, fragmentShaderSource);
	if (!sp->isCompiled())
	{
		std::cerr << "Can't load shader program:\n"
				  << "Vertex: " << vertexShader << "\n"
				  << "Fragment: " << fragmentShader << std::endl;
		return nullptr;
	}

	_shaderStorage.emplace(shaderName, sp);
	return sp;
}

std::shared_ptr<render::ShaderProgram> ResourceManager::getShader(const std::string & shaderName) const
{
	if (auto it = _shaderStorage.find(shaderName); it != _shaderStorage.end())
	{
		return it->second;
	}

	std::cerr << "Can't find shared program \"" << shaderName << "\"" << std::endl;

	return nullptr;
}

std::shared_ptr<render::Texture2D> ResourceManager::loadTexture(const std::string & textureName, const std::string & texturePath)
{
	int channels = 0, width = 0, height = 0;

	stbi_set_flip_vertically_on_load(1);
	stbi_uc * pixels = stbi_load(getPath(texturePath).c_str(), &width, &height, &channels, 0);
	if (!pixels)
	{
		std::cerr << "Can't load texture \"" << texturePath << "\"" << std::endl;
		return nullptr;
	}
	auto sp = _textureStorage.emplace(
								 textureName,
								 std::make_shared<render::Texture2D>(width, height, pixels, channels, GL_NEAREST, GL_CLAMP_TO_EDGE))
				  .first->second;

	stbi_image_free(pixels);

	return sp;
}

std::shared_ptr<render::Texture2D> ResourceManager::getTexture(const std::string & textureName) const
{
	if (auto it = _textureStorage.find(textureName); it != _textureStorage.end())
	{
		return it->second;
	}

	std::cerr << "Can't find texture \"" << textureName << "\"" << std::endl;

	return nullptr;
}

std::shared_ptr<render::Sprite> ResourceManager::loadSprite(
	const std::string & spriteName,
	const std::string & shaderName,
	const std::string & textureName,
	const float spriteWeight,
	const float spriteHeight,
	const std::string & subTextureName)
{
	auto texture = getTexture(textureName);
	if (!texture)
	{
		std::cerr << "can't find texture " << textureName << " for sprite " << spriteName << std::endl;
		return nullptr;
	}

	auto shader = getShader(shaderName);
	if (!shader)
	{
		std::cerr << "can't find shader " << shaderName << " for sprite " << spriteName << std::endl;
		return nullptr;
	}

	return _spriteStorage.emplace(spriteName,
								  std::make_shared<render::Sprite>(
									  texture,
									  subTextureName,
									  shader,
									  glm::vec2(0.0F, 0.0F),
									  glm::vec2(spriteWeight, spriteHeight)))
		.first->second;
}

std::shared_ptr<render::Sprite> ResourceManager::getSprite(const std::string & spriteName) const
{
	if (auto it = _spriteStorage.find(spriteName); it != _spriteStorage.end())
	{
		return it->second;
	}

	std::cerr << "can't find sprite \"" << spriteName << "\"" << std::endl;

	return nullptr;
}

std::shared_ptr<render::Texture2D> ResourceManager::loadTextureAtlas(const std::string & textureName, const std::string & texturePath, const std::vector<std::string> & subTextures, const int subTextureWidth, const int subTextureHeight)
{
	auto spTexture = loadTexture(textureName, texturePath);

	if (!spTexture)
	{
		std::cerr << "can't find texture \"" << textureName << "\" for atlas" << std::endl;
		return nullptr;
	}

	const int textureWidth = spTexture->width();
	const int textureHeight = spTexture->height();
	int currentTextureOffsetX = 0;
	int currentTextureOffsetY = textureHeight;

	for (const auto & currentSubTextureName: subTextures)
	{
		glm::vec2 leftBottomUV(static_cast<float>(currentTextureOffsetX) / textureWidth, static_cast<float>(currentTextureOffsetY - subTextureHeight) / textureHeight);
		glm::vec2 rightTopUV(static_cast<float>(currentTextureOffsetX + subTextureWidth) / textureWidth, static_cast<float>(currentTextureOffsetY) / textureHeight);

		spTexture->addSubTexture(currentSubTextureName, leftBottomUV, rightTopUV);

		currentTextureOffsetX += subTextureWidth;
		if (currentTextureOffsetX >= textureWidth)
		{
			currentTextureOffsetX = 0;
			currentTextureOffsetY -= subTextureHeight;
		}
	}

	return spTexture;
}

std::string ResourceManager::getPath(const std::string & relativePath) const
{
	return _pathToExecutable + pathSeparator + relativePath;
}

std::string ResourceManager::readFile(const std::string & relativePathToFile) const
{
	std::ifstream file(getPath(relativePathToFile), std::ios_base::in & std::ios_base::binary);

	if (!file.is_open())
	{
		std::cerr << "Failed opening file: " << relativePathToFile << std::endl;
		return "";
	}

	std::stringstream fullFile;
	fullFile << file.rdbuf();

	return fullFile.str();
}
}// namespace resources