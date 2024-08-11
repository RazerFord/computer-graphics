#pragma once

#include <glad/glad.h>
#include <glm/ext/matrix_float4x4.hpp>
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

	void setInt(const std::string & name, const GLint value) const;
	void setFloat(const std::string & name, const GLfloat value) const;
	void setMat4(const std::string & name, const glm::mat4 & value) const;

	bool isCompiled() const;

	operator bool() const;

private:
	void safeReset() noexcept;
	void reset() noexcept;
};
}// namespace render