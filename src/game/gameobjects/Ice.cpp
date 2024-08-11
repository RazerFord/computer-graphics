#include "Ice.hpp"
#include "../../render/Sprite.hpp"
#include "../../resources/ResourceManager.hpp"
#include "IGameObject.hpp"

namespace game
{
Ice::Ice(const resources::ResourceManager & manager, const glm::vec2 & position, const glm::vec2 & size, const float rotation, const float layer)
	: IGameObject(position, size, rotation, layer)
	, _sprite{manager.getSprite("ice")}
	, _offsets{
		  glm::vec2(0.0F, _size.y / 2.0F),
		  glm::vec2(_size.x / 2.0F, _size.y / 2.0F),
		  glm::vec2(0.0F, 0.0F),
		  glm::vec2(_size.x / 2.0F, 0.0F),
	  }
{}

void Ice::render() const
{
	for (const auto location: {
			 IceLocation::TopLeft,
			 IceLocation::TopRight,
			 IceLocation::BottomLeft,
			 IceLocation::BottomRight,
		 })
	{
		renderBrick(location);
	}
}

void Ice::renderBrick(const IceLocation & location) const
{
	_sprite->render(_position + _offsets[static_cast<size_t>(location)], _size / 2.0F, _rotation, _layer);
}
}// namespace game