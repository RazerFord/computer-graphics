#include "RenderProgram.hpp"
#include <iostream>

namespace render
{
GLuint createShader(const std::string & shaderSource, const GLenum type, const bool printLog = true);

template <typename Get, typename Info>
std::string readInfoLog(const GLuint shader, int & success, const Get get, const Info info);

ShaderProgram::ShaderProgram(const std::string & vertexShaderSource, const std::string & fragmentShaderSource)
{
	GLuint vertexShader = createShader(vertexShaderSource, GL_VERTEX_SHADER);
	if (vertexShader == 0)
	{
		return;
	}

	GLuint fragmentShader = createShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
	if (fragmentShader == 0)
	{
		glDeleteShader(vertexShader);
		return;
	}

	_programID = glCreateProgram();
	glAttachShader(_programID, vertexShader);
	glAttachShader(_programID, fragmentShader);
	glLinkProgram(_programID);

	int success;
	std::string infoLog = readInfoLog(_programID, success, glGetProgramiv, glGetProgramInfoLog);
	if (success == 0)
	{
		std::cerr << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	_isCompiled = success != 0;
}

ShaderProgram::ShaderProgram(ShaderProgram && shaderProgram)
{
	safeReset();

	_isCompiled = shaderProgram._isCompiled;
	_programID = shaderProgram._programID;

	shaderProgram._programID = 0;
	shaderProgram._isCompiled = false;
}

ShaderProgram::~ShaderProgram()
{
	safeReset();
}

ShaderProgram & ShaderProgram::operator=(ShaderProgram && shaderProgram) noexcept
{
	if (this == &shaderProgram)
	{
		return *this;
	}

	safeReset();

	_isCompiled = shaderProgram._isCompiled;
	_programID = shaderProgram._programID;

	shaderProgram._programID = 0;
	shaderProgram._isCompiled = false;

	return *this;
}

void ShaderProgram::use() const
{
	glUseProgram(_programID);
}

void ShaderProgram::safeReset() noexcept
{
	if (_isCompiled)
	{
		reset();
	}
}

void ShaderProgram::reset() noexcept
{
	_isCompiled = false;
	glDeleteProgram(_programID);
}

bool ShaderProgram::isCompiled() const
{
	return _isCompiled;
}

ShaderProgram::operator bool() const
{
	return _isCompiled;
}

GLuint createShader(const std::string & shaderSource, const GLenum type, const bool printLog)
{
	const char * const source = shaderSource.c_str();
	int success;

	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	std::string infoLog = readInfoLog(shader, success, glGetShaderiv, glGetShaderInfoLog);
	if (success == 0)
	{
		if (printLog)
		{
			std::cerr << infoLog << std::endl;
		}
		return 0;
	}

	return shader;
}

template <typename Get, typename Info>
std::string readInfoLog(const GLuint shader, int & success, const Get get, const Info info)
{
	char infoLog[1024];

	get(shader, GL_COMPILE_STATUS, &success);

	if (success == 0)
	{
		info(shader, 1024, nullptr, infoLog);
		return {infoLog};
	}

	return "";
}
}// namespace render