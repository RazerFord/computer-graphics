#pragma once

#include <glm/vec2.hpp>
#include <memory>

#include "IGameObject.hpp"
#include "Orientation.hpp"

#include "../../render/SpriteAnimator.hpp"
#include "../../utils/Timer.hpp"

namespace resources
{
class ResourceManager;
}

namespace physics
{
class PhysicsEngine;
}

namespace render
{
class Sprite;
}

namespace game
{
class Bullet;

class Tank : public IGameObject
{
private:
	Orientation _orientation;
	std::shared_ptr<render::Sprite> _spriteUp;
	std::shared_ptr<render::Sprite> _spriteRight;
	std::shared_ptr<render::Sprite> _spriteDown;
	std::shared_ptr<render::Sprite> _spriteLeft;
	std::shared_ptr<render::Sprite> _spriteRespawn;
	std::shared_ptr<render::Sprite> _spriteShield;
	render::SpriteAnimator _spriteAnimatorUp;
	render::SpriteAnimator _spriteAnimatorRight;
	render::SpriteAnimator _spriteAnimatorDown;
	render::SpriteAnimator _spriteAnimatorLeft;
	render::SpriteAnimator _spriteAnimatorRespawn;
	render::SpriteAnimator _spriteAnimatorShield;

	double _maxVelocity;
	bool _isSpawning;
	bool _hasShield;

	utils::Timer _respawnTimer;
	utils::Timer _shieldTimer;

	std::shared_ptr<Bullet> _bullet;
	std::shared_ptr<physics::PhysicsEngine> _physicsEngine;

public:
	Tank(const std::shared_ptr<render::Sprite> & spriteUp,
		 const std::shared_ptr<render::Sprite> & spriteRight,
		 const std::shared_ptr<render::Sprite> & spriteDown,
		 const std::shared_ptr<render::Sprite> & spriteLeft,
		 const std::shared_ptr<physics::PhysicsEngine> & physicsEngine,
		 const resources::ResourceManager & manager,
		 const double maxVelocity,
		 const glm::vec2 & position,
		 const glm::vec2 & size,
		 const float layer);

	void render() const override;
	void update(const double delta) override;
	void setOrientation(const Orientation orientation);

	void velocity(const double velocity) override;

	double maxVelocity() const;

	void fire();
};
}// namespace game