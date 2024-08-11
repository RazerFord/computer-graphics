#include "Sprite.hpp"

#include "IndexBuffer.hpp"
#include "Render.hpp"
#include "ShaderProgram.hpp"
#include "Texture2D.hpp"
#include "VertexArray.hpp"
#include "VertexBufferLayout.hpp"
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
	const std::shared_ptr<ShaderProgram> & spShaderProgram)
	: _spTexture2D(spTexture2D)
	, _spShaderProgram(spShaderProgram)
	, _lastFrame(0)
{
	const render::Texture2D::SubTexture2D & st = _spTexture2D->getSubTexture(initialSubTexture);

	const GLfloat textureCoords[]{
		st.leftBottomUV.x, st.leftBottomUV.y,
		st.leftBottomUV.x, st.rightTopUV.y,
		st.rightTopUV.x, st.rightTopUV.y,
		st.rightTopUV.x, st.leftBottomUV.y};

	_vertexArray.bind();

	_vertexCoordsBuffer.init(vertexCoords, sizeof(vertexCoords));
	VertexBufferLayout vertexLayout;
	vertexLayout.addElementLayoutFloat(2, GL_FALSE);
	_vertexArray.addBuffer(_vertexCoordsBuffer, vertexLayout);

	_textureCoordsBuffer.init(textureCoords, sizeof(textureCoords));
	VertexBufferLayout textureLayout;
	textureLayout.addElementLayoutFloat(2, GL_FALSE);
	_vertexArray.addBuffer(_textureCoordsBuffer, textureLayout);

	_vertexArray.bind();

	_indexBuffer.init(indices, sizeof(indices) / sizeof(GLuint));

	_vertexArray.unbind();
	_indexBuffer.unbind();
}

Sprite::~Sprite()
{}

void Sprite::render(const glm::vec2 & position, const glm::vec2 & size, const float rotation, const size_t frame)
{
	if (_lastFrame != frame)
	{
		_lastFrame = frame;

		const auto frameDescription = _framesDescription[frame];
		const GLfloat textureCoords[]{
			frameDescription.leftBottomUV.x, frameDescription.leftBottomUV.y,
			frameDescription.leftBottomUV.x, frameDescription.rightTopUV.y,
			frameDescription.rightTopUV.x, frameDescription.rightTopUV.y,
			frameDescription.rightTopUV.x, frameDescription.leftBottomUV.y};

		_textureCoordsBuffer.update(textureCoords, sizeof(textureCoords));
	}

	_spShaderProgram->use();

	glm::mat4 model(1.0F);

	model = glm::translate(model, glm::vec3(position, 0.0F));
	model = glm::translate(model, glm::vec3(0.5F * size.x, 0.5F * size.y, 0.0F));
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0F, 0.0F, 1.0F));
	model = glm::translate(model, glm::vec3(-0.5F * size.x, -0.5F * size.y, 0.0F));
	model = glm::scale(model, glm::vec3(size, 1.0));

	_spShaderProgram->setMat4("modelMat", model);

	glActiveTexture(GL_TEXTURE0);
	_spTexture2D->bind();

	Render::draw(_vertexArray, _indexBuffer, *_spShaderProgram);
}

size_t Sprite::getFrameDuration(const size_t frame) const
{
	return _framesDescription[frame].duration;
}

size_t Sprite::getFramesCount() const
{
	return _framesDescription.size();
}

void Sprite::setFrames(const std::vector<FrameDescription> & framesDescription)
{
	_framesDescription = framesDescription;
}
}// namespace render