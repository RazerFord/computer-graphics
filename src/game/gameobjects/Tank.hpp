#pragma once

#include <glm/vec2.hpp>
#include <memory>

#include "IGameObject.hpp"

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

class Tank : public IGameObject
{
private:
	Orientation _orientation;
	std::shared_ptr<render::AnimatedSprite> _animatedSprite;
	float _velocity;
	glm::vec2 _moveOffset;
	bool _move;

public:
	Tank(const std::shared_ptr<render::AnimatedSprite> & spAnimatedSprite, const float velocity, const glm::vec2 & position, const glm::vec2 & size);

	void render() const override;
	void update(const size_t delta) override;
	void setOrientation(const Orientation orientation);
	void setMove(const bool move);
};
}// namespace game