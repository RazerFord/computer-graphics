#include "Tank.hpp"
#include "../../render/Sprite.hpp"
#include "IGameObject.hpp"

namespace game
{
Tank::Tank(const std::shared_ptr<render::Sprite> & spriteUp,
		   const std::shared_ptr<render::Sprite> & spriteRight,
		   const std::shared_ptr<render::Sprite> & spriteDown,
		   const std::shared_ptr<render::Sprite> & spriteLeft,
		   const float velocity,
		   const glm::vec2 & position,
		   const glm::vec2 & size)
	: IGameObject(position, size, 0.0F)
	, _orientation(Orientation::Up)
	, _spriteUp(spriteUp)
	, _spriteRight(spriteRight)
	, _spriteDown(spriteDown)
	, _spriteLeft(spriteLeft)
	, _spriteAnimatorUp(spriteUp)
	, _spriteAnimatorRight(spriteRight)
	, _spriteAnimatorDown(spriteDown)
	, _spriteAnimatorLeft(spriteLeft)
	, _velocity(velocity)
	, _moveOffset(0.0F, 1.0F)
	, _move(false)
{}

void Tank::render() const
{
	switch (_orientation)
	{
		case game::Orientation::Up: {
			_spriteUp->render(_position, _size, _rotation, _spriteAnimatorUp.getCurrentFrame());
			break;
		}
		case game::Orientation::Down: {
			_spriteDown->render(_position, _size, _rotation, _spriteAnimatorDown.getCurrentFrame());
			break;
		}
		case game::Orientation::Left: {
			_spriteLeft->render(_position, _size, _rotation, _spriteAnimatorLeft.getCurrentFrame());
			break;
		}
		case game::Orientation::Right: {
			_spriteRight->render(_position, _size, _rotation, _spriteAnimatorRight.getCurrentFrame());
			break;
		}
	}
}

void Tank::update(const size_t delta)
{
	if (_move)
	{
		_position += delta * _velocity * _moveOffset;
		switch (_orientation)
		{
			case game::Orientation::Up: {
				_spriteAnimatorUp.update(delta);
				break;
			}
			case game::Orientation::Down: {
				_spriteAnimatorDown.update(delta);
				break;
			}
			case game::Orientation::Left: {
				_spriteAnimatorLeft.update(delta);
				break;
			}
			case game::Orientation::Right: {
				_spriteAnimatorRight.update(delta);
				break;
			}
		}
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
			_moveOffset = {0.0, 1.0};
			break;
		}
		case game::Orientation::Down: {
			_moveOffset = {0.0, -1.0};
			break;
		}
		case game::Orientation::Left: {
			_moveOffset = {-1.0, 0.0};
			break;
		}
		case game::Orientation::Right: {
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