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
class Ice : public IGameObject
{
public:
	enum class IceLocation
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
	Ice(const resources::ResourceManager & manager, const glm::vec2 & position, const glm::vec2 & size, const float rotation);

	virtual void render() const override;

private:
	void renderBrick(const IceLocation & location) const;
};
}// namespace game