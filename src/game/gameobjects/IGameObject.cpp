#include "IGameObject.hpp"

namespace game
{
IGameObject::IGameObject(const GameObjectType & gameObjectType, const glm::vec2 & position, const glm::vec2 & size, const float rotation, const float layer)
	: _gameObjectType(gameObjectType)
	, _position(position)
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

const glm::vec2 & IGameObject::size() const
{
	return _size;
}

const glm::vec2 & IGameObject::direction() const
{
	return _direction;
}

double IGameObject::velocity() const
{
	return _velocity;
}

const std::vector<physics::Collider> & IGameObject::colliders() const
{
	return _colliders;
}

IGameObject::GameObjectType IGameObject::gameObjectType() const
{
	return _gameObjectType;
}

void IGameObject::position(const glm::vec2 & position)
{
	_position = position;
}

void IGameObject::velocity(const double velocity)
{
	_velocity = velocity;
}

bool IGameObject::colliders(const GameObjectType & gameObjectType) const
{
	return true;
}

void IGameObject::update(const double delta)
{}

void IGameObject::onCollision()
{}
}// namespace game