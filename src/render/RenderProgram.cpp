#include "RenderProgram.hpp"
#include <iostream>

namespace render
{
GLuint createShader(const std::string & shaderSource, const GLenum type, const bool printLog = true);

template <typename Get, typename Info>
std::string readInfoLog(const GLuint shader, int & success, const Get get, const Info info);

RenderProgram::RenderProgram(const std::string & vertexShaderSource, const std::string & fragmentShaderSource)
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

RenderProgram::RenderProgram(RenderProgram && renderProgram)
{
	safeReset();

	_isCompiled = renderProgram._isCompiled;
	_programID = renderProgram._programID;

	renderProgram._programID = 0;
	renderProgram._isCompiled = false;
}

RenderProgram::~RenderProgram()
{
	safeReset();
}

RenderProgram & RenderProgram::operator=(RenderProgram && renderProgram) noexcept
{
	if (this == &renderProgram)
	{
		return *this;
	}

	safeReset();

	_isCompiled = renderProgram._isCompiled;
	_programID = renderProgram._programID;

	renderProgram._programID = 0;
	renderProgram._isCompiled = false;

	return *this;
}

void RenderProgram::use() const
{
	glUseProgram(_programID);
}

void RenderProgram::safeReset() noexcept
{
	if (_isCompiled)
	{
		reset();
	}
}

void RenderProgram::reset() noexcept
{
	_isCompiled = false;
	glDeleteProgram(_programID);
}

bool RenderProgram::isCompiled() const
{
	return _isCompiled;
}

RenderProgram::operator bool() const
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