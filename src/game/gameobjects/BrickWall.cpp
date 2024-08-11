#include "BrickWall.hpp"
#include "../../render/Sprite.hpp"
#include "../../resources/ResourceManager.hpp"
#include "IGameObject.hpp"

namespace game
{
BrickWall::BrickWall(const BrickWallType & type, const resources::ResourceManager & manager, const glm::vec2 & position, const glm::vec2 & size, const float rotation)
	: IGameObject(position, size, rotation)
	, _states{
		  BrickWall::BrickState::Destroyed,
		  BrickWall::BrickState::Destroyed,
		  BrickWall::BrickState::Destroyed,
		  BrickWall::BrickState::Destroyed,
	  }
	, _offsets{
		  glm::vec2(0.0F, _size.y / 2.0F),
		  glm::vec2(_size.x / 2.0F, _size.y / 2.0F),
		  glm::vec2(0.0F, 0.0F),
		  glm::vec2(_size.x / 2.0F, 0.0F),
	  }
{
	_sprites[static_cast<size_t>(BrickState::All)] = manager.getSprite("brickWall_All");
	_sprites[static_cast<size_t>(BrickState::TopLeft)] = manager.getSprite("brickWall_TopLeft");
	_sprites[static_cast<size_t>(BrickState::TopRight)] = manager.getSprite("brickWall_TopRight");
	_sprites[static_cast<size_t>(BrickState::Top)] = manager.getSprite("brickWall_Top");
	_sprites[static_cast<size_t>(BrickState::BottomLeft)] = manager.getSprite("brickWall_BottomLeft");
	_sprites[static_cast<size_t>(BrickState::Left)] = manager.getSprite("brickWall_Left");
	_sprites[static_cast<size_t>(BrickState::TopRight_BottomLeft)] = manager.getSprite("brickWall_TopRight_BottomLeft");
	_sprites[static_cast<size_t>(BrickState::Top_BottomLeft)] = manager.getSprite("brickWall_Top_BottomLeft");
	_sprites[static_cast<size_t>(BrickState::BottomRight)] = manager.getSprite("brickWall_BottomRight");
	_sprites[static_cast<size_t>(BrickState::TopLeft_BottomRight)] = manager.getSprite("brickWall_TopLeft_BottomRight");
	_sprites[static_cast<size_t>(BrickState::Right)] = manager.getSprite("brickWall_Right");
	_sprites[static_cast<size_t>(BrickState::Top_BottomRight)] = manager.getSprite("brickWall_Top_BottomRight");
	_sprites[static_cast<size_t>(BrickState::Bottom)] = manager.getSprite("brickWall_Bottom");
	_sprites[static_cast<size_t>(BrickState::TopLeft_Bottom)] = manager.getSprite("brickWall_TopLeft_Bottom");
	_sprites[static_cast<size_t>(BrickState::TopRight_Bottom)] = manager.getSprite("brickWall_TopRight_Bottom");

	switch (type)
	{
		case BrickWallType::All: {
			_states[static_cast<size_t>(BrickLocation::TopLeft)] = BrickState::All;
			_states[static_cast<size_t>(BrickLocation::TopRight)] = BrickState::All;
			_states[static_cast<size_t>(BrickLocation::BottomLeft)] = BrickState::All;
			_states[static_cast<size_t>(BrickLocation::BottomRight)] = BrickState::All;
			break;
		}
		case BrickWallType::Top: {
			_states[static_cast<size_t>(BrickLocation::TopLeft)] = BrickState::All;
			_states[static_cast<size_t>(BrickLocation::TopRight)] = BrickState::All;
			break;
		}
		case BrickWallType::Left: {
			_states[static_cast<size_t>(BrickLocation::TopLeft)] = BrickState::All;
			_states[static_cast<size_t>(BrickLocation::BottomLeft)] = BrickState::All;
			break;
		}
		case BrickWallType::Right: {
			_states[static_cast<size_t>(BrickLocation::TopRight)] = BrickState::All;
			_states[static_cast<size_t>(BrickLocation::BottomRight)] = BrickState::All;
			break;
		}
		case BrickWallType::Bottom: {
			_states[static_cast<size_t>(BrickLocation::BottomLeft)] = BrickState::All;
			_states[static_cast<size_t>(BrickLocation::BottomRight)] = BrickState::All;
			break;
		}
		case BrickWallType::TopLeft: {
			_states[static_cast<size_t>(BrickLocation::TopLeft)] = BrickState::All;
			break;
		}
		case BrickWallType::TopRight: {
			_states[static_cast<size_t>(BrickLocation::TopRight)] = BrickState::All;
			break;
		}
		case BrickWallType::BottomLeft: {
			_states[static_cast<size_t>(BrickLocation::BottomLeft)] = BrickState::All;
			break;
		}
		case BrickWallType::BottomRight: {
			_states[static_cast<size_t>(BrickLocation::BottomRight)] = BrickState::All;
			break;
		}
	}
}

void BrickWall::render() const
{
	for (const auto location: {
			 BrickLocation::TopLeft,
			 BrickLocation::TopRight,
			 BrickLocation::BottomLeft,
			 BrickLocation::BottomRight,
		 })
	{
		renderBrick(location);
	}
}

void BrickWall::update(const size_t delta)
{
	// BrickWall static object
}

void BrickWall::renderBrick(const BrickLocation & location) const
{
	const size_t index = static_cast<size_t>(location);
	const auto state = _states[index];
	if (state != BrickState::Destroyed)
	{
		_sprites[static_cast<size_t>(state)]->render(_position + _offsets[index], _size / 2.0F, _rotation);
	}
}

}// namespace game