#pragma once

#include <glad/glad.h>
#include <string>

namespace render
{
class ShaderProgram
{
private:
	bool _isCompiled = false;
	GLuint _programID = 0;

public:
	ShaderProgram(const std::string & vertexShaderSource, const std::string & fragmentShaderSource);
	ShaderProgram(ShaderProgram && shaderProgram);
	~ShaderProgram();

	ShaderProgram & operator=(ShaderProgram && shaderProgram) noexcept;

	void use() const;

	bool isCompiled() const;

	operator bool() const;

private:
	void safeReset() noexcept;
	void reset() noexcept;
};
}// namespace render