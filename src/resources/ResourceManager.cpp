#include "ResourceManager.hpp"
#include "../render/ShaderProgram.hpp"
#include "../render/Sprite.hpp"
#include "../render/Texture2D.hpp"
#include "rapidjson/error/error.h"
#include <fstream>
#include <ios>
#include <iostream>
#include <memory>
#include <rapidjson/document.h>
#include <rapidjson/error/en.h>
#include <sstream>
#include <string>
#include <vector>

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

const float offsetForTexture = 0.001F;

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
									  shader))
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
		glm::vec2 leftBottomUV(static_cast<float>(currentTextureOffsetX + offsetForTexture) / textureWidth, static_cast<float>(currentTextureOffsetY - subTextureHeight + offsetForTexture) / textureHeight);
		glm::vec2 rightTopUV(static_cast<float>(currentTextureOffsetX + subTextureWidth - offsetForTexture) / textureWidth, static_cast<float>(currentTextureOffsetY - offsetForTexture) / textureHeight);

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

bool ResourceManager::loadJSON(const std::string & JSONPath)
{
	const std::string json = readFile(JSONPath);
	if (json.empty())
	{
		std::cerr << "can't opening json file \"" << JSONPath << "\"" << std::endl;
		return false;
	}

	rapidjson::Document document;
	rapidjson::ParseResult parseResult = document.Parse(json.c_str());

	if (!parseResult)
	{
		std::cerr << "json parsing error \"" << rapidjson::GetParseError_En(parseResult.Code()) << "\"" << std::endl;
		std::cerr << "filepath \"" << JSONPath << "\"" << std::endl;
		std::cerr << "offset " << parseResult.Offset() << std::endl;
		return false;
	}

	auto shadersIterator = document.FindMember("shaders");
	if (shadersIterator != document.MemberEnd())
	{
		for (const auto & currentShader: shadersIterator->value.GetArray())
		{
			const std::string name = currentShader["name"].GetString();
			const std::string filePathVertexShader = currentShader["filePathVertexShader"].GetString();
			const std::string filePathFragmentShader = currentShader["filePathFragmentShader"].GetString();

			auto program = loadShader(name, filePathVertexShader, filePathFragmentShader);
			if (!program)
			{
				std::cerr << "can't create shader program \"" << name << "\"" << std::endl;
				return false;
			}
		}
	}

	auto textureAtlasIterator = document.FindMember("textureAtlases");
	if (textureAtlasIterator != document.MemberEnd())
	{
		for (const auto & currentTextureAtlas: textureAtlasIterator->value.GetArray())
		{
			const std::string name = currentTextureAtlas["name"].GetString();
			const std::string filePathTexture = currentTextureAtlas["filePath"].GetString();
			const int subTextureWidth = currentTextureAtlas["subTextureWidth"].GetInt();
			const int subTextureHeight = currentTextureAtlas["subTextureHeight"].GetInt();

			const auto subTextureNamesArray = currentTextureAtlas["subTextures"].GetArray();
			std::vector<std::string> subTextureNames;
			for (const auto & subTextureName: subTextureNamesArray)
			{
				subTextureNames.push_back(subTextureName.GetString());
			}

			auto textureAtlas = loadTextureAtlas(name, filePathTexture, subTextureNames, subTextureWidth, subTextureHeight);
			if (!textureAtlas)
			{
				std::cerr << "can't create texture atlas \"" << name << "\"" << std::endl;
				return false;
			}
		}
	}

	auto spritesIterator = document.FindMember("sprites");
	if (spritesIterator != document.MemberEnd())
	{
		for (const auto & currentSprite: spritesIterator->value.GetArray())
		{
			const std::string name = currentSprite["name"].GetString();
			const std::string shader = currentSprite["shader"].GetString();
			const std::string textureAtlas = currentSprite["textureAtlas"].GetString();
			const std::string initSubTextureName = currentSprite["initialSubTexture"].GetString();

			auto sprite = loadSprite(name, shader, textureAtlas, initSubTextureName);
			if (!sprite)
			{
				std::cerr << "can't create sprite \"" << "tankSprite" << "\"" << std::endl;
				return false;
			}

			auto framesIterator = currentSprite.FindMember("frames");
			if (framesIterator != currentSprite.MemberEnd())
			{
				std::vector<render::Sprite::FrameDescription> framesDescription;
				for (const auto & frame: framesIterator->value.GetArray())
				{
					const std::string subTextureName = frame["subTexture"].GetString();
					const size_t duration = frame["duration"].GetUint64();
					const auto subTexture = getTexture(textureAtlas)->getSubTexture(subTextureName);
					framesDescription.push_back({subTexture.leftBottomUV, subTexture.rightTopUV, duration});
				}
				sprite->setFrames(framesDescription);
			}
		}
	}

	auto levelsIterator = document.FindMember("levels");
	if (levelsIterator != document.MemberEnd())
	{
		for (const auto & currentLevel: levelsIterator->value.GetArray())
		{
			const auto description = currentLevel["description"].GetArray();
			std::vector<std::string> levelRows;
			size_t maxLen = 0;
			for (const auto & row: description)
			{
				levelRows.push_back(row.GetString());
				maxLen = std::max(levelRows.back().size(), maxLen);
			}

			for (auto & row: levelRows)
			{
				row.resize(maxLen, 'D');
			}

			_levels.emplace_back(std::move(levelRows));
		}
	}

	return true;
}

const ResourceManager::LevelStorage & ResourceManager::levels() const
{
	return _levels;
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