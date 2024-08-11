#include "Water.hpp"
#include "../../render/Sprite.hpp"
#include "../../resources/ResourceManager.hpp"
#include "IGameObject.hpp"

namespace game
{
Water::Water(const resources::ResourceManager & manager, const glm::vec2 & position, const glm::vec2 & size, const float rotation, const float layer)
	: IGameObject(position, size, rotation, layer)
	, _sprite{manager.getSprite("water")}
	, _spriteAnimator{_sprite}
	, _offsets{
		  glm::vec2(0.0F, _size.y / 2.0F),
		  glm::vec2(_size.x / 2.0F, _size.y / 2.0F),
		  glm::vec2(0.0F, 0.0F),
		  glm::vec2(_size.x / 2.0F, 0.0F),
	  }
{}

void Water::render() const
{
	for (const auto location: {
			 WaterLocation::TopLeft,
			 WaterLocation::TopRight,
			 WaterLocation::BottomLeft,
			 WaterLocation::BottomRight,
		 })
	{
		renderBrick(location);
	}
}

void Water::update(const size_t delta)
{
	_spriteAnimator.update(delta);
}


void Water::renderBrick(const WaterLocation & location) const
{
	_sprite->render(_position + _offsets[static_cast<size_t>(location)], _size / 2.0F, _rotation, _layer, _spriteAnimator.getCurrentFrame());
}
}// namespace game