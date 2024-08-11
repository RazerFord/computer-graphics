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

public:
	IGameObject(const glm::vec2 & position, const glm::vec2 & size, const float rotation);

	virtual void render() const = 0;
	virtual void update(const size_t delta);
	virtual ~IGameObject() = default;
};
}// namespace game