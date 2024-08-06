#include "Sprite.hpp"

#include "ShaderProgram.hpp"
#include "Texture2D.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>

namespace render
{
const GLfloat vertexCoords[] = {
	0.0F, 0.0F,
	0.0F, 1.0F,
	1.0F, 1.0F,

	1.0F, 1.0F,
	1.0F, 0.0F,
	0.0F, 0.0F};

const GLfloat textureCoords[]{
	0.0F, 0.0F,
	0.0F, 1.0F,
	1.0F, 1.0F,

	1.0F, 1.0F,
	1.0F, 0.0F,
	0.0F, 0.0F};

Sprite::Sprite(
	const std::shared_ptr<Texture2D> & spTexture2D,
	const std::shared_ptr<ShaderProgram> & spShaderProgram,
	const glm::vec2 & position,
	const glm::vec2 & size,
	const float rotation)
	: _spTexture2D(spTexture2D)
	, _spShaderProgram(spShaderProgram)
	, _position(position)
	, _size(size)
	, _rotation(rotation)
{
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glCreateBuffers(1, &_vertexCoordsVbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexCoordsVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexCoords), vertexCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	glCreateBuffers(1, &_textureCoordsVbo);
	glBindBuffer(GL_ARRAY_BUFFER, _textureCoordsVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoords), textureCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Sprite::~Sprite()
{
	glDeleteBuffers(1, &_vertexCoordsVbo);
	glDeleteBuffers(1, &_textureCoordsVbo);
	glDeleteVertexArrays(1, &_vao);
}

void Sprite::render() const
{
	_spShaderProgram->use();

	glm::mat4 model(1.0F);

	model = glm::translate(model, glm::vec3(_position, 0.0F));
	model = glm::translate(model, glm::vec3(0.5F * _size.x, 0.5F * _size.y, 0.0F));
	model = glm::rotate(model, glm::radians(_rotation), glm::vec3(0.0F, 0.0F, 1.0F));
	model = glm::translate(model, glm::vec3(-0.5F * _size.x, -0.5F * _size.y, 0.0F));
	model = glm::scale(model, glm::vec3(_size, 1.0));

	glBindVertexArray(_vao);

	_spShaderProgram->setMat4("modelMat", model);

	glActiveTexture(GL_TEXTURE0);
	_spTexture2D->bind();

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	// _spShaderProgram->setMat4("projectionMat", model);
}

void Sprite::setPosition(const glm::vec2 & position)
{
	_position = position;
}

void Sprite::setSize(const glm::vec2 & size)
{
	_size = size;
}

void Sprite::setRotation(const float rotation)
{
	_rotation = rotation;
}
}// namespace render