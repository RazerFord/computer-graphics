#include "Tank.hpp"
#include "../../render/Sprite.hpp"
#include "IGameObject.hpp"

namespace game
{
Tank::Tank(const std::shared_ptr<render::Sprite> & spriteUp,
		   const std::shared_ptr<render::Sprite> & spriteRight,
		   const std::shared_ptr<render::Sprite> & spriteDown,
		   const std::shared_ptr<render::Sprite> & spriteLeft,
		   const std::shared_ptr<render::Sprite> & spriteRespawn,
		   const std::shared_ptr<render::Sprite> & spriteShield,
		   const double velocity,
		   const glm::vec2 & position,
		   const glm::vec2 & size,
		   const float layer)
	: IGameObject(position, size, 0.0F, layer)
	, _orientation(Orientation::Up)
	, _spriteUp(spriteUp)
	, _spriteRight(spriteRight)
	, _spriteDown(spriteDown)
	, _spriteLeft(spriteLeft)
	, _spriteRespawn(spriteRespawn)
	, _spriteShield(spriteShield)
	, _spriteAnimatorUp(spriteUp)
	, _spriteAnimatorRight(spriteRight)
	, _spriteAnimatorDown(spriteDown)
	, _spriteAnimatorLeft(spriteLeft)
	, _spriteAnimatorRespawn(spriteRespawn)
	, _spriteAnimatorShield(spriteShield)
	, _velocity(velocity)
	, _moveOffset(0.0F, 1.0F)
	, _move(false)
	, _isSpawning(true)
	, _hasShield(false)
{
	_respawnTimer.setCallback([this]() {
		_isSpawning = false;
		_hasShield = true;
		_shieldTimer.start(2000);
	});

	_shieldTimer.setCallback([this]() {
		_hasShield = false;
	});

	_respawnTimer.start(2000);
}

void Tank::render() const
{
	if (_isSpawning)
	{
		_spriteRespawn->render(_position, _size, _rotation, _layer, _spriteAnimatorRespawn.getCurrentFrame());
	}
	else
	{
		switch (_orientation)
		{
			case game::Orientation::Up: {
				_spriteUp->render(_position, _size, _rotation, _layer, _spriteAnimatorUp.getCurrentFrame());
				break;
			}
			case game::Orientation::Down: {
				_spriteDown->render(_position, _size, _rotation, _layer, _spriteAnimatorDown.getCurrentFrame());
				break;
			}
			case game::Orientation::Left: {
				_spriteLeft->render(_position, _size, _rotation, _layer, _spriteAnimatorLeft.getCurrentFrame());
				break;
			}
			case game::Orientation::Right: {
				_spriteRight->render(_position, _size, _rotation, _layer, _spriteAnimatorRight.getCurrentFrame());
				break;
			}
		}

		if (_hasShield)
		{
			_spriteShield->render(_position, _size, _rotation, _layer, _spriteAnimatorShield.getCurrentFrame());
		}
	}
}

void Tank::update(const double delta)
{
	if (_isSpawning)
	{
		_spriteAnimatorRespawn.update(delta);
		_respawnTimer.update(delta);
	}
	else
	{
		if (_hasShield)
		{
			_spriteAnimatorShield.update(delta);
			_shieldTimer.update(delta);
		}

		if (_move)
		{
			_position.x += delta * _velocity * _moveOffset.x;
			_position.y += delta * _velocity * _moveOffset.y;

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