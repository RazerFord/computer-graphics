#pragma once

#include "../../physics/PhysicsEngine.hpp"
#include <glm/vec2.hpp>

namespace game
{
class IGameObject
{
public:
	enum class GameObjectType
	{
		Border,
		BrickWall,
		Bullet,
		ConcreteWall,
		Eagle,
		Ice,
		Tank,
		Trees,
		Water,
		Unknow,
	};

protected:
	GameObjectType _gameObjectType;
	glm::vec2 _position;
	glm::vec2 _size;
	float _rotation;
	float _layer;
	glm::vec2 _direction;
	double _velocity;
	std::vector<physics::Collider> _colliders;

public:
	IGameObject(const GameObjectType & gameObjectType, const glm::vec2 & position, const glm::vec2 & size, const float rotation, const float layer);

	const glm::vec2 & position() const;
	const glm::vec2 & size() const;
	const glm::vec2 & direction() const;
	double velocity() const;
	const std::vector<physics::Collider> & colliders() const;
	GameObjectType gameObjectType() const;

	virtual void position(const glm::vec2 & position);
	virtual void velocity(const double velocity);

	virtual bool colliders(const GameObjectType & gameObjectType) const;
	virtual void render() const = 0;
	virtual void update(const double delta);
	virtual void onCollision();
	virtual ~IGameObject() = default;
};
}// namespace game