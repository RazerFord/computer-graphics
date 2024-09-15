#pragma once

#include <glm/vec2.hpp>
#include <memory>

#include "IGameObject.hpp"
#include "Orientation.hpp"

#include "../../render/SpriteAnimator.hpp"
#include "../../utils/Timer.hpp"

namespace render
{
class Sprite;
}// namespace render

namespace game
{
class Bullet : public IGameObject
{
private:
	Orientation _orientation;
	std::shared_ptr<render::Sprite> _spriteUp;
	std::shared_ptr<render::Sprite> _spriteRight;
	std::shared_ptr<render::Sprite> _spriteDown;
	std::shared_ptr<render::Sprite> _spriteLeft;
	std::shared_ptr<render::Sprite> _spriteExplosion;
	bool _isActive;
	double _maxVelocity;
	glm::vec2 _explosionSize;
	glm::vec2 _explosionOffset;
	render::SpriteAnimator _spriteAnimatorExplosion;
	utils::Timer _timerExplosion;
	bool _isExplosion;

public:
	Bullet(const std::shared_ptr<render::Sprite> & spriteUp,
		   const std::shared_ptr<render::Sprite> & spriteRight,
		   const std::shared_ptr<render::Sprite> & spriteDown,
		   const std::shared_ptr<render::Sprite> & spriteLeft,
		   const std::shared_ptr<render::Sprite> & spriteExplosion,
		   const double velocity,
		   const glm::vec2 & position,
		   const glm::vec2 & size,
		   const glm::vec2 & explosionSize,
		   const float layer);

	virtual void render() const override;
	virtual void update(const double delta) override;

	bool isActive() const;

	void fire(const glm::vec2 & position, const glm::vec2 & direction);
};
}// namespace game