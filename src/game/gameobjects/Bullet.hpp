#pragma once

#include <glm/vec2.hpp>
#include <memory>

#include "IGameObject.hpp"
#include "Orientation.hpp"

namespace render
{
class Sprite;
}

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
	bool _isActive;

public:
	Bullet(const std::shared_ptr<render::Sprite> & spriteUp,
		   const std::shared_ptr<render::Sprite> & spriteRight,
		   const std::shared_ptr<render::Sprite> & spriteDown,
		   const std::shared_ptr<render::Sprite> & spriteLeft,
		   const double velocity,
		   const glm::vec2 & position,
		   const glm::vec2 & size,
		   const float layer);

	void render() const override;

	bool isActive() const;

	void fire(const glm::vec2 & position, const glm::vec2 & direction);
};
}// namespace game