#pragma once

#include <glm/vec2.hpp>
#include <memory>

namespace render
{
class AnimatedSprite;
}

namespace game
{
enum class Orientation
{
	Up,
	Down,
	Left,
	Right,
};

class Tank
{
private:
	Orientation _orientation;
	std::shared_ptr<render::AnimatedSprite> _animatedSprite;
	float _velocity;
	glm::vec2 _position;
	glm::vec2 _moveOffset;
	bool _move;

public:
	Tank(const std::shared_ptr<render::AnimatedSprite> & spAnimatedSprite, const float velocity, const glm::vec2 & position);

	void render() const;
	void update(const size_t delta);
	void setOrientation(const Orientation orientation);
	void setMove(const bool move);
};
}// namespace game