#pragma once

#include "IGameObject.hpp"
#include <array>
#include <glm/vec2.hpp>
#include <memory>

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
class BrickWall : public IGameObject
{
public:
	enum class BrickWallType
	{
		All,
		Top,
		Left,
		Right,
		Bottom,
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight,
	};

	enum class BrickState
	{
		All,
		TopLeft,
		TopRight,
		Top,
		BottomLeft,
		Left,
		TopRight_BottomLeft,
		Top_BottomLeft,
		BottomRight,
		TopLeft_BottomRight,
		Right,
		Top_BottomRight,
		Bottom,
		TopLeft_Bottom,
		TopRight_Bottom,
		Destroyed,
	};

	enum class BrickLocation
	{
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight,
	};

private:
	std::array<std::shared_ptr<render::Sprite>, 15> _sprites;
	std::array<BrickState, 4> _states;
	const std::array<glm::vec2, 4> _offsets;

public:
	BrickWall(const BrickWallType & type, const resources::ResourceManager & manager, const glm::vec2 & position, const glm::vec2 & size, const float rotation);

	virtual void render() const override;
	virtual void update(const size_t delta) override;

private:
	void renderBrick(const BrickLocation & location) const;
};
}// namespace game