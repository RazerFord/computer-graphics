#include "IGameObject.hpp"

namespace game
{
IGameObject::IGameObject(const glm::vec2 & position, const glm::vec2 & size, const float rotation, const float layer)
	: _position(position)
	, _size(size)
	, _rotation(rotation)
	, _layer(layer)
{}

void IGameObject::update(const double delta)
{}
}// namespace game