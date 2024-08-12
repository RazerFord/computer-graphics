#pragma once

#include "IGameObject.hpp"
#include <array>
#include <glm/vec2.hpp>
#include <memory>

#include "../../render/SpriteAnimator.hpp"

namespace resources
{
class ResourceManager;
}

namespace render
{
class Sprite;
}

namespace game
{
class Water : public IGameObject
{
public:
	enum class WaterLocation
	{
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight,
	};

private:
	std::shared_ptr<render::Sprite> _sprite;
	render::SpriteAnimator _spriteAnimator;
	const std::array<glm::vec2, 4> _offsets;

public:
	Water(const resources::ResourceManager & manager, const glm::vec2 & position, const glm::vec2 & size, const float rotation, const float layer);

	virtual void render() const override;

	virtual void update(const double delta) override;

private:
	void renderBrick(const WaterLocation & location) const;
};
}// namespace game