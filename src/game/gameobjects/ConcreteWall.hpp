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
class ConcreteWall : public IGameObject
{
public:
	enum class ConcreteWallType
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

	enum class ConcreteState
	{
		Built,
		Destroyed,
	};

	enum class BlockLocation
	{
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight,
	};

private:
	std::shared_ptr<render::Sprite> _sprite;
	std::array<ConcreteState, 4> _states;
	const std::array<glm::vec2, 4> _offsets;

public:
	ConcreteWall(const ConcreteWallType & type, const resources::ResourceManager & manager, const glm::vec2 & position, const glm::vec2 & size, const float rotation, const float layer);

	virtual void render() const override;
	virtual void update(const size_t delta) override;

private:
	void renderBlock(const BlockLocation & location) const;
};
}// namespace game