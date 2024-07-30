#include "ResourceManager.hpp"
#include "../render/ShaderProgram.hpp"
#include <fstream>
#include <ios>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

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

	_storage.emplace(shaderName, sp);
	return sp;
}

std::shared_ptr<render::ShaderProgram> ResourceManager::getShader(const std::string & shaderName) const
{
	if (auto it = _storage.find(shaderName); it != _storage.end())
	{
		return it->second;
	}

	std::cerr << "Can't find shared program \"" << shaderName << "\"" << std::endl;

	return nullptr;
}


std::string ResourceManager::readFile(const std::string & relativePathToFile) const
{
	std::ifstream file(_pathToExecutable + pathSeparator + relativePathToFile, std::ios_base::in & std::ios_base::binary);

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