#pragma once

#include <memory>
#include <string>
#include <unordered_map>

namespace render
{
class ShaderProgram;
}

namespace resources
{
class ResourceManager
{
private:
	using ShaderStorage = std::unordered_map<std::string, std::shared_ptr<render::ShaderProgram>>;

	const std::string _pathToExecutable;
	ShaderStorage _storage;

public:
	ResourceManager(const std::string & pathToExecutable);
	~ResourceManager() = default;

	std::shared_ptr<render::ShaderProgram> loadShader(const std::string & shaderName, const std::string & vertexShader, const std::string & fragmentShader);
	std::shared_ptr<render::ShaderProgram> getShader(const std::string & shaderName) const;

	void loadTexture(const std::string & textureName, const std::string & texturePath);

private:
	std::string getPath(const std::string & relativePath) const;
	std::string readFile(const std::string & relativePathToFile) const;
};
}// namespace resources