#pragma once

#include <glad/glad.h>
#include <string>

namespace render
{
class RenderProgram
{
private:
	bool _isCompiled = false;
	GLuint _programID = 0;

public:
	RenderProgram(const std::string & vertexShaderSource, const std::string & fragmentShaderSource);
	RenderProgram(RenderProgram && renderProgram);
	~RenderProgram();

	RenderProgram & operator=(RenderProgram && renderProgram) noexcept;

	void use() const;

	bool isCompiled() const;

	operator bool() const;

private:
	void safeReset() noexcept;
	void reset() noexcept;
};
}// namespace render