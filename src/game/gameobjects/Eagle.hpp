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
class Eagle : public IGameObject
{
public:
	enum class EagleState
	{
		Alive,
		Dead,
	};

private:
	std::array<std::shared_ptr<render::Sprite>, 2> _sprites;
	EagleState _currentState;

public:
	Eagle(const resources::ResourceManager & manager, const glm::vec2 & position, const glm::vec2 & size, const float rotation, const float layer);

	virtual void render() const override;
	virtual void update(const size_t delta) override;
};
}// namespace game