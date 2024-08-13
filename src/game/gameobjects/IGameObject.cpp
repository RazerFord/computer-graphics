#include "IGameObject.hpp"

namespace game
{
IGameObject::IGameObject(const glm::vec2 & position, const glm::vec2 & size, const float rotation, const float layer)
	: _position(position)
	, _size(size)
	, _rotation(rotation)
	, _layer(layer)
	, _direction(0.0F, 1.0F)
	, _velocity(0.0F)
{}

const glm::vec2 & IGameObject::position() const
{
	return _position;
}

const glm::vec2 & IGameObject::direction() const
{
	return _direction;
}

double IGameObject::velocity() const
{
	return _velocity;
}

void IGameObject::position(const glm::vec2 & position)
{
	_position = position;
}

void IGameObject::velocity(const double velocity)
{
	_velocity = velocity;
}

void IGameObject::update(const double delta)
{}
}// namespace game