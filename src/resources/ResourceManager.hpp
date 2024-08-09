#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace render
{
class ShaderProgram;
class Texture2D;
class Sprite;
class AnimatedSprite;
}// namespace render

namespace resources
{
class ResourceManager
{
private:
	using ShaderStorage = std::unordered_map<std::string, std::shared_ptr<render::ShaderProgram>>;
	using TextureStorage = std::unordered_map<std::string, std::shared_ptr<render::Texture2D>>;
	using SpriteStorage = std::unordered_map<std::string, std::shared_ptr<render::Sprite>>;
	using AnimatedSpriteStorage = std::unordered_map<std::string, std::shared_ptr<render::AnimatedSprite>>;
	using LevelStorage = std::vector<std::vector<std::string>>;

	const std::string _pathToExecutable;
	ShaderStorage _shaderStorage;
	TextureStorage _textureStorage;
	SpriteStorage _spriteStorage;
	AnimatedSpriteStorage _animatedSpriteStorage;
	LevelStorage _levels;

public:
	ResourceManager(const std::string & pathToExecutable);
	~ResourceManager() = default;

	std::shared_ptr<render::ShaderProgram> loadShader(const std::string & shaderName, const std::string & vertexShader, const std::string & fragmentShader);
	std::shared_ptr<render::ShaderProgram> getShader(const std::string & shaderName) const;

	std::shared_ptr<render::Texture2D> loadTexture(const std::string & textureName, const std::string & texturePath);
	std::shared_ptr<render::Texture2D> getTexture(const std::string & textureName) const;

	std::shared_ptr<render::Sprite> loadSprite(const std::string & spriteName, const std::string & shaderName, const std::string & textureName, const std::string & subTextureName = "default");
	std::shared_ptr<render::Sprite> getSprite(const std::string & spriteName) const;

	std::shared_ptr<render::Texture2D> loadTextureAtlas(const std::string & textureName, const std::string & texturePath, const std::vector<std::string> & subTextures, const int subTextureWidth, const int subTextureHeight);

	std::shared_ptr<render::AnimatedSprite> loadAnimatedSprite(const std::string & spriteName, const std::string & shaderName, const std::string & textureName, const std::string & subTextureName = "default");
	std::shared_ptr<render::AnimatedSprite> getAnimatedSprite(const std::string & spriteName) const;

	bool loadJSON(const std::string & JSONPath);

	const LevelStorage& levels() const;

private:
	std::string getPath(const std::string & relativePath) const;
	std::string readFile(const std::string & relativePathToFile) const;
};
}// namespace resources