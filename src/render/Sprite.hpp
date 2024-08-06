#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <memory>

namespace render
{
class Texture2D;
class ShaderProgram;

class Sprite
{
private:
	std::shared_ptr<Texture2D> _spTexture2D;
	std::shared_ptr<ShaderProgram> _spShaderProgram;
	glm::vec2 _position;
	glm::vec2 _size;
	float _rotation;
	GLuint _vao;
	GLuint _vertexCoordsVbo;
	GLuint _textureCoordsVbo;

public:
	Sprite(
		const std::shared_ptr<Texture2D> & spTexture2D,
		const std::shared_ptr<ShaderProgram> & spShaderProgram,
		const glm::vec2 & position = glm::vec2(0.0F),
		const glm::vec2 & size = glm::vec2(1.0F),
		const float rotation = 0.0F);

	void render() const;

	void setPosition(const glm::vec2 & position);
	void setSize(const glm::vec2 & size);
	void setRotation(const float rotation);

	~Sprite();
};
}// namespace render