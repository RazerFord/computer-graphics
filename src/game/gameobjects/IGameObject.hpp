#pragma once

#include "../../physics/PhysicsEngine.hpp"
#include <glm/vec2.hpp>

namespace game
{
class IGameObject
{
protected:
	glm::vec2 _position;
	glm::vec2 _size;
	float _rotation;
	float _layer;
	glm::vec2 _direction;
	double _velocity;
	std::vector<physics::AABB> _colliders;

public:
	IGameObject(const glm::vec2 & position, const glm::vec2 & size, const float rotation, const float layer);

	const glm::vec2 & position() const;
	const glm::vec2 & size() const;
	const glm::vec2 & direction() const;
	double velocity() const;
	const std::vector<physics::AABB> colliders() const;

	virtual void position(const glm::vec2 & position);
	virtual void velocity(const double velocity);

	virtual void render() const = 0;
	virtual void update(const double delta);
	virtual ~IGameObject() = default;
};
}// namespace game