#include "Tank.hpp"
#include "../render/AnimatedSprite.hpp"

namespace game
{
Tank::Tank(const std::shared_ptr<render::AnimatedSprite> & spAnimatedSprite, const float velocity, const glm::vec2 & position)
	: _orientation(Orientation::Up)
	, _animatedSprite(spAnimatedSprite)
	, _velocity(velocity)
	, _position(position)
	, _moveOffset(0.0F, 1.0F)
	, _move(false)
{
	_animatedSprite->setPosition(_position);
}

void Tank::render() const
{
	_animatedSprite->render();
}

void Tank::update(const size_t delta)
{
	if (_move)
	{
		_position += delta * _velocity * _moveOffset;
		_animatedSprite->setPosition(_position);
		_animatedSprite->update(delta);
	}
}

void Tank::setOrientation(const Orientation orientation)
{
	if (orientation == _orientation)
	{
		return;
	}

	_orientation = orientation;
	switch (_orientation)
	{
		case game::Orientation::Up: {
			_animatedSprite->setState("tankUpState");
			_moveOffset = {0.0, 1.0};
			break;
		}
		case game::Orientation::Down: {
			_animatedSprite->setState("tankDownState");
			_moveOffset = {0.0, -1.0};
			break;
		}
		case game::Orientation::Left: {
			_animatedSprite->setState("tankLeftState");
			_moveOffset = {-1.0, 0.0};
			break;
		}
		case game::Orientation::Right: {
			_animatedSprite->setState("tankRightState");
			_moveOffset = {1.0, 0.0};
			break;
		}
	}
}

void Tank::setMove(const bool move)
{
	_move = move;
}

}// namespace game