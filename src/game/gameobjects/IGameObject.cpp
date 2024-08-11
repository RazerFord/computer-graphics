#include "IGameObject.hpp"

namespace game
{
IGameObject::IGameObject(const glm::vec2 & position, const glm::vec2 & size, const float rotation)
	: _position(position)
	, _size(size)
	, _rotation(rotation)
{}

void IGameObject::update(const size_t delta)
{}
}// namespace game