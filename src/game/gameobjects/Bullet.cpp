#include "Bullet.hpp"
#include "../../render/Sprite.hpp"
#include "IGameObject.hpp"

namespace game
{
Bullet::Bullet(const std::shared_ptr<render::Sprite> & spriteUp,
			   const std::shared_ptr<render::Sprite> & spriteRight,
			   const std::shared_ptr<render::Sprite> & spriteDown,
			   const std::shared_ptr<render::Sprite> & spriteLeft,
			   const std::shared_ptr<render::Sprite> & spriteExplosion,
			   const double velocity,
			   const glm::vec2 & position,
			   const glm::vec2 & size,
			   const glm::vec2 & explosionSize,
			   const float layer)
	: IGameObject(GameObjectType::Bullet, position, size, 0.0F, layer)
	, _orientation(Orientation::Up)
	, _spriteUp(spriteUp)
	, _spriteRight(spriteRight)
	, _spriteDown(spriteDown)
	, _spriteLeft(spriteLeft)
	, _spriteExplosion(spriteExplosion)
	, _isActive(false)
	, _maxVelocity(velocity)
	, _explosionSize(explosionSize)
	, _explosionOffset((_explosionSize - _size) / 2.0F)
	, _spriteAnimatorExplosion(spriteExplosion)
	, _isExplosion(false)
{
	_colliders.push_back({glm::vec2(0), _size});
	_timerExplosion.setCallback([this]() {
		_isExplosion = false;
		_isActive = false;
	});
}

void Bullet::render() const
{
	if (_isActive)
	{
		if (_isExplosion)
		{
			switch (_orientation)
			{
				case game::Orientation::Up: {
					_spriteExplosion->render(_position - _explosionOffset + glm::vec2(0.0F, _size.y / 2.0F), _explosionSize, _rotation, _layer);
					break;
				}
				case game::Orientation::Down: {
					_spriteExplosion->render(_position - _explosionOffset - glm::vec2(0.0F, _size.y / 2.0F), _explosionSize, _rotation, _layer);
					break;
				}
				case game::Orientation::Left: {
					_spriteExplosion->render(_position - _explosionOffset - glm::vec2(_size.x / 2.0F, 0.0F), _explosionSize, _rotation, _layer);
					break;
				}
				case game::Orientation::Right: {
					_spriteExplosion->render(_position - _explosionOffset + glm::vec2(_size.x / 2.0F, 0.0F), _explosionSize, _rotation, _layer);
					break;
				}
			}
		}
		else
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
	}
}

void Bullet::update(const double delta)
{
	if (_isExplosion)
	{
		_spriteAnimatorExplosion.update(delta);
		_timerExplosion.update(delta);
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
	_velocity = _maxVelocity;
}

void Bullet::onCollision()
{
	_velocity = 0.0F;
	_isExplosion = true;
	_spriteAnimatorExplosion.reset();
	_timerExplosion.start(_spriteAnimatorExplosion.getTotalDuration());
}
}// namespace game