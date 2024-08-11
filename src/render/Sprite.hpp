#pragma once

#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <memory>
#include <string>
#include <vector>

namespace render
{
class Texture2D;
class ShaderProgram;

class Sprite
{
public:
	struct FrameDescription {
		glm::vec2 leftBottomUV;
		glm::vec2 rightTopUV;
		size_t duration;
	};

protected:
	std::shared_ptr<Texture2D> _spTexture2D;
	std::shared_ptr<ShaderProgram> _spShaderProgram;
	VertexArray _vertexArray;
	IndexBuffer _indexBuffer;
	VertexBuffer _vertexCoordsBuffer;
	VertexBuffer _textureCoordsBuffer;
	std::vector<FrameDescription> _framesDescription;
	size_t _lastFrame;

public:
	Sprite(
		const std::shared_ptr<Texture2D> & spTexture2D,
		const std::string & initialSubTexture,
		const std::shared_ptr<ShaderProgram> & spShaderProgram);

	void render(const glm::vec2 & position, const glm::vec2 & size, const float rotation, const size_t frame = 0);

	size_t getFrameDuration(const size_t frame) const;
	size_t getFramesCount() const;

	void setFrames(const std::vector<FrameDescription> & framesDescription);

	~Sprite();
};
}// namespace render