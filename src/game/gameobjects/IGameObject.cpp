#include "IGameObject.hpp"

namespace game
{
IGameObject::IGameObject(const glm::vec2 & position, const glm::vec2 & size, const float rotation)
	: _position(position)
	, _size(size)
	, _rotation(rotation)
{}
}// namespace game