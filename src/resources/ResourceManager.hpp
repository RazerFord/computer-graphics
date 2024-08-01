#pragma once

#include <memory>
#include <string>
#include <unordered_map>

namespace render
{
class ShaderProgram;
class Texture2D;
}// namespace render

namespace resources
{
class ResourceManager
{
private:
	using ShaderStorage = std::unordered_map<std::string, std::shared_ptr<render::ShaderProgram>>;
	using TextureStorage = std::unordered_map<std::string, std::shared_ptr<render::Texture2D>>;

	const std::string _pathToExecutable;
	ShaderStorage _shaderStorage;
	TextureStorage _textureStorage;

public:
	ResourceManager(const std::string & pathToExecutable);
	~ResourceManager() = default;

	std::shared_ptr<render::ShaderProgram> loadShader(const std::string & shaderName, const std::string & vertexShader, const std::string & fragmentShader);
	std::shared_ptr<render::ShaderProgram> getShader(const std::string & shaderName) const;

	std::shared_ptr<render::Texture2D> loadTexture(const std::string & textureName, const std::string & texturePath);
	std::shared_ptr<render::Texture2D> getTexture(const std::string & textureName) const;

private:
	std::string getPath(const std::string & relativePath) const;
	std::string readFile(const std::string & relativePathToFile) const;
};
}// namespace resources