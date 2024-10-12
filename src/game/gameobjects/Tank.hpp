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
public:
	enum class ETank
	{
		Player1YellowTankType1,
		Player1YellowTankType2,
		Player1YellowTankType3,
		Player1YellowTankType4,

		Player2GreenTankType1,
		Player2GreenTankType2,
		Player2GreenTankType3,
		Player2GreenTankType4,

		EnemyWhiteTankType1,
		EnemyWhiteTankType2,
		EnemyWhiteTankType3,
		EnemyWhiteTankType4,

		EnemyGreenTankType1,
		EnemyGreenTankType2,
		EnemyGreenTankType3,
		EnemyGreenTankType4,

		EnemyRedTankType1,
		EnemyRedTankType2,
		EnemyRedTankType3,
		EnemyRedTankType4,
	};

	static const std::vector<std::string> TankTypeToSpriteString;
	const std::string& getTankSpriteFromType(const ETank type);

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
	Tank(const ETank type,
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