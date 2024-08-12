#pragma once

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

public:
	IGameObject(const glm::vec2 & position, const glm::vec2 & size, const float rotation, const float layer);

	virtual void render() const = 0;
	virtual void update(const double delta);
	virtual ~IGameObject() = default;
};
}// namespace game