#include "Sprite.hpp"

#include "IndexBuffer.hpp"
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
	1.0F, 0.0F};

const GLuint indices[] = {
	0, 1, 2,
	0, 2, 3};

Sprite::Sprite(
	const std::shared_ptr<Texture2D> & spTexture2D,
	const std::string & initialSubTexture,
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
	const render::Texture2D::SubTexture2D & st = _spTexture2D->getSubTexture(initialSubTexture);

	const GLfloat textureCoords[]{
		st.leftBottomUV.x, st.leftBottomUV.y,
		st.leftBottomUV.x, st.rightTopUV.y,
		st.rightTopUV.x, st.rightTopUV.y,
		st.rightTopUV.x, st.leftBottomUV.y};

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	_vertexCoordsBuffer.init(vertexCoords, sizeof(vertexCoords));
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	_textureCoordsBuffer.init(textureCoords, sizeof(textureCoords));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
	glEnableVertexAttribArray(1);

	_indexBuffer.init(indices, sizeof(indices));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Sprite::~Sprite()
{
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

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
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