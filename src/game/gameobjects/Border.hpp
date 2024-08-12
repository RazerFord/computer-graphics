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
class Border : public IGameObject
{
public:
	enum class BorderLocation
	{
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight,
	};

private:
	std::shared_ptr<render::Sprite> _sprite;

public:
	Border(const resources::ResourceManager & manager, const glm::vec2 & position, const glm::vec2 & size, const float rotation, const float layer);

	virtual void render() const override;

private:
	void renderBrick(const BorderLocation & location) const;
};
}// namespace game