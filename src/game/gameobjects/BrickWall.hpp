#pragma once

#include "IGameObject.hpp"
#include <glm/vec2.hpp>
#include <memory>

namespace render
{
class Sprite;
}

namespace game
{
class BrickWall : public IGameObject
{
private:
	std::shared_ptr<render::Sprite> _sprite;

public:
	BrickWall(const std::shared_ptr<render::Sprite> & sprite, const glm::vec2 & position, const glm::vec2 & size, const float rotation);

	virtual void render() const override;
	virtual void update(const size_t delta) override;
};
}// namespace game