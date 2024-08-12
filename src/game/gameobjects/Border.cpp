#include "Border.hpp"
#include "../../render/Sprite.hpp"
#include "../../resources/ResourceManager.hpp"
#include "IGameObject.hpp"

namespace game
{
Border::Border(const resources::ResourceManager & manager, const glm::vec2 & position, const glm::vec2 & size, const float rotation, const float layer)
	: IGameObject(position, size, rotation, layer)
	, _sprite{manager.getSprite("border")}
{}

void Border::render() const
{
	_sprite->render(_position, _size, _rotation, _layer);
}
}// namespace game