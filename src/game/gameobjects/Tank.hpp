#pragma once

#include <glm/vec2.hpp>
#include <memory>

#include "../../render/SpriteAnimator.hpp"
#include "IGameObject.hpp"

#include "../../utils/Timer.hpp"

namespace render
{
class Sprite;
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

	double _velocity;
	glm::vec2 _moveOffset;
	bool _move;
	bool _isSpawning;
	bool _hasShield;

	utils::Timer _respawnTimer;
	utils::Timer _shieldTimer;

public:
	Tank(const std::shared_ptr<render::Sprite> & spriteUp,
		 const std::shared_ptr<render::Sprite> & spriteRight,
		 const std::shared_ptr<render::Sprite> & spriteDown,
		 const std::shared_ptr<render::Sprite> & spriteLeft,
		 const std::shared_ptr<render::Sprite> & spriteRespawn,
		 const std::shared_ptr<render::Sprite> & spriteShield,
		 const double velocity,
		 const glm::vec2 & position,
		 const glm::vec2 & size,
		 const float layer);

	void render() const override;
	void update(const double delta) override;
	void setOrientation(const Orientation orientation);
	void setMove(const bool move);
};
}// namespace game