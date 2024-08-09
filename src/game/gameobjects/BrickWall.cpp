#include "BrickWall.hpp"
#include "IGameObject.hpp"
#include "../../render/Sprite.hpp"

namespace game
{
BrickWall::BrickWall(const std::shared_ptr<render::Sprite> & sprite, const glm::vec2 & position, const glm::vec2 & size, const float rotation)
	: IGameObject(position, size, rotation)
	, _sprite(sprite)
{}

void BrickWall::render() const
{
    _sprite->render(_position, _size, _rotation);
}

void BrickWall::update(const size_t delta)
{
    // BrickWall static object
}
}// namespace game