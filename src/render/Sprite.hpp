#pragma once

#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <memory>
#include <string>

namespace render
{
class Texture2D;
class ShaderProgram;

class Sprite
{
protected:
	std::shared_ptr<Texture2D> _spTexture2D;
	std::shared_ptr<ShaderProgram> _spShaderProgram;
	VertexArray _vertexArray;
	IndexBuffer _indexBuffer;
	VertexBuffer _vertexCoordsBuffer;
	VertexBuffer _textureCoordsBuffer;
	glm::vec2 _currentLeftBottomUV;
	glm::vec2 _currentRightTopUV;

public:
	Sprite(
		const std::shared_ptr<Texture2D> & spTexture2D,
		const std::string & initialSubTexture,
		const std::shared_ptr<ShaderProgram> & spShaderProgram);

	virtual void render(const glm::vec2 & position, const glm::vec2 & size, const float rotation) const;

	virtual ~Sprite();
};
}// namespace render