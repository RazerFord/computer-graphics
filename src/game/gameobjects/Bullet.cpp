#include "Bullet.hpp"
#include "../../render/Sprite.hpp"
#include "IGameObject.hpp"

namespace game
{
Bullet::Bullet(const std::shared_ptr<render::Sprite> & spriteUp,
			   const std::shared_ptr<render::Sprite> & spriteRight,
			   const std::shared_ptr<render::Sprite> & spriteDown,
			   const std::shared_ptr<render::Sprite> & spriteLeft,
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
	, _isActive(false)
{
	_velocity = velocity;
	_colliders.push_back({glm::vec2(0), _size});
}

void Bullet::render() const
{
	switch (_orientation)
	{
		case game::Orientation::Up: {
			_spriteUp->render(_position, _size, _rotation, _layer);
			break;
		}
		case game::Orientation::Down: {
			_spriteDown->render(_position, _size, _rotation, _layer);
			break;
		}
		case game::Orientation::Left: {
			_spriteLeft->render(_position, _size, _rotation, _layer);
			break;
		}
		case game::Orientation::Right: {
			_spriteRight->render(_position, _size, _rotation, _layer);
			break;
		}
	}
}

bool Bullet::isActive() const
{
	return _isActive;
}

void Bullet::fire(const glm::vec2 & position, const glm::vec2 & direction)
{
	_position = position;
	_direction = direction;
	if (_direction.x == 0.0)
	{
		_orientation = _direction.y > 0.0 ? Orientation::Up : Orientation::Down;
	}
	else
	{
		_orientation = _direction.x > 0.0 ? Orientation::Right : Orientation::Left;
	}
	_isActive = true;
}
}// namespace game