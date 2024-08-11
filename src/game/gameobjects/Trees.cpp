#include "Trees.hpp"
#include "../../render/Sprite.hpp"
#include "../../resources/ResourceManager.hpp"
#include "IGameObject.hpp"

namespace game
{
Trees::Trees(const resources::ResourceManager & manager, const glm::vec2 & position, const glm::vec2 & size, const float rotation)
	: IGameObject(position, size, rotation)
	, _sprite{manager.getSprite("trees")}
	, _offsets{
		  glm::vec2(0.0F, _size.y / 2.0F),
		  glm::vec2(_size.x / 2.0F, _size.y / 2.0F),
		  glm::vec2(0.0F, 0.0F),
		  glm::vec2(_size.x / 2.0F, 0.0F),
	  }
{}

void Trees::render() const
{
	for (const auto location: {
			 TreesLocation::TopLeft,
			 TreesLocation::TopRight,
			 TreesLocation::BottomLeft,
			 TreesLocation::BottomRight,
		 })
	{
		renderBrick(location);
	}
}

void Trees::renderBrick(const TreesLocation & location) const
{
	_sprite->render(_position + _offsets[static_cast<size_t>(location)], _size / 2.0F, _rotation);
}
}// namespace game