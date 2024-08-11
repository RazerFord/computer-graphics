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
class Trees : public IGameObject
{
public:
	enum class TreesLocation
	{
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight,
	};

private:
	std::shared_ptr<render::Sprite> _sprite;
	const std::array<glm::vec2, 4> _offsets;

public:
	Trees(const resources::ResourceManager & manager, const glm::vec2 & position, const glm::vec2 & size, const float rotation, const float layer);

	virtual void render() const override;

private:
	void renderBrick(const TreesLocation & location) const;
};
}// namespace game