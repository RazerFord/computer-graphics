#include "BrickWall.hpp"
#include "../../render/Sprite.hpp"
#include "../../resources/ResourceManager.hpp"
#include "IGameObject.hpp"

namespace game
{
BrickWall::BrickWall(const BrickWallType & type, const resources::ResourceManager & manager, const glm::vec2 & position, const glm::vec2 & size, const float rotation, const float layer)
	: IGameObject(GameObjectType::BrickWall, position, size, rotation, layer)
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

	auto onCollisionCallbackTopLeft = [&](const IGameObject & object, const physics::CollisionDirection direction) {
		onCollisionCallback(BrickLocation::TopLeft, object, direction);
	};
	auto onCollisionCallbackTopRight = [&](const IGameObject & object, const physics::CollisionDirection direction) {
		onCollisionCallback(BrickLocation::TopRight, object, direction);
	};
	auto onCollisionCallbackBottomRight = [&](const IGameObject & object, const physics::CollisionDirection direction) {
		onCollisionCallback(BrickLocation::BottomRight, object, direction);
	};
	auto onCollisionCallbackBottomLeft = [&](const IGameObject & object, const physics::CollisionDirection direction) {
		onCollisionCallback(BrickLocation::BottomLeft, object, direction);
	};

	_brickLocationToColliderMap.fill(nullptr);
	_colliders.reserve(4);

	switch (type)
	{
		case BrickWallType::All: {
			_states[static_cast<size_t>(BrickLocation::TopLeft)] = BrickState::All;
			_states[static_cast<size_t>(BrickLocation::TopRight)] = BrickState::All;
			_states[static_cast<size_t>(BrickLocation::BottomLeft)] = BrickState::All;
			_states[static_cast<size_t>(BrickLocation::BottomRight)] = BrickState::All;
			_brickLocationToColliderMap[static_cast<size_t>(BrickLocation::TopLeft)] = &_colliders.emplace_back(getAABBForBrickState(BrickLocation::TopLeft, BrickState::All, _size), onCollisionCallbackTopLeft);
			_brickLocationToColliderMap[static_cast<size_t>(BrickLocation::TopRight)] = &_colliders.emplace_back(getAABBForBrickState(BrickLocation::TopRight, BrickState::All, _size), onCollisionCallbackTopRight);
			_brickLocationToColliderMap[static_cast<size_t>(BrickLocation::BottomLeft)] = &_colliders.emplace_back(getAABBForBrickState(BrickLocation::BottomLeft, BrickState::All, _size), onCollisionCallbackBottomLeft);
			_brickLocationToColliderMap[static_cast<size_t>(BrickLocation::BottomRight)] = &_colliders.emplace_back(getAABBForBrickState(BrickLocation::BottomRight, BrickState::All, _size), onCollisionCallbackBottomRight);
			break;
		}
		case BrickWallType::Top: {
			_states[static_cast<size_t>(BrickLocation::TopLeft)] = BrickState::All;
			_states[static_cast<size_t>(BrickLocation::TopRight)] = BrickState::All;
			_brickLocationToColliderMap[static_cast<size_t>(BrickLocation::TopLeft)] = &_colliders.emplace_back(getAABBForBrickState(BrickLocation::TopLeft, BrickState::All, _size), onCollisionCallbackTopLeft);
			_brickLocationToColliderMap[static_cast<size_t>(BrickLocation::TopRight)] = &_colliders.emplace_back(getAABBForBrickState(BrickLocation::TopRight, BrickState::All, _size), onCollisionCallbackTopRight);
			break;
		}
		case BrickWallType::Left: {
			_states[static_cast<size_t>(BrickLocation::TopLeft)] = BrickState::All;
			_states[static_cast<size_t>(BrickLocation::BottomLeft)] = BrickState::All;
			_brickLocationToColliderMap[static_cast<size_t>(BrickLocation::TopLeft)] = &_colliders.emplace_back(getAABBForBrickState(BrickLocation::TopLeft, BrickState::All, _size), onCollisionCallbackTopLeft);
			_brickLocationToColliderMap[static_cast<size_t>(BrickLocation::BottomLeft)] = &_colliders.emplace_back(getAABBForBrickState(BrickLocation::BottomLeft, BrickState::All, _size), onCollisionCallbackBottomLeft);
			break;
		}
		case BrickWallType::Right: {
			_states[static_cast<size_t>(BrickLocation::TopRight)] = BrickState::All;
			_states[static_cast<size_t>(BrickLocation::BottomRight)] = BrickState::All;
			_brickLocationToColliderMap[static_cast<size_t>(BrickLocation::TopRight)] = &_colliders.emplace_back(getAABBForBrickState(BrickLocation::TopRight, BrickState::All, _size), onCollisionCallbackTopRight);
			_brickLocationToColliderMap[static_cast<size_t>(BrickLocation::BottomRight)] = &_colliders.emplace_back(getAABBForBrickState(BrickLocation::BottomRight, BrickState::All, _size), onCollisionCallbackBottomRight);
			break;
		}
		case BrickWallType::Bottom: {
			_states[static_cast<size_t>(BrickLocation::BottomLeft)] = BrickState::All;
			_states[static_cast<size_t>(BrickLocation::BottomRight)] = BrickState::All;
			_brickLocationToColliderMap[static_cast<size_t>(BrickLocation::BottomLeft)] = &_colliders.emplace_back(getAABBForBrickState(BrickLocation::BottomLeft, BrickState::All, _size), onCollisionCallbackBottomLeft);
			_brickLocationToColliderMap[static_cast<size_t>(BrickLocation::BottomRight)] = &_colliders.emplace_back(getAABBForBrickState(BrickLocation::BottomRight, BrickState::All, _size), onCollisionCallbackBottomRight);
			break;
		}
		case BrickWallType::TopLeft: {
			_states[static_cast<size_t>(BrickLocation::TopLeft)] = BrickState::All;
			_brickLocationToColliderMap[static_cast<size_t>(BrickLocation::TopLeft)] = &_colliders.emplace_back(getAABBForBrickState(BrickLocation::TopLeft, BrickState::All, _size), onCollisionCallbackTopLeft);
			break;
		}
		case BrickWallType::TopRight: {
			_states[static_cast<size_t>(BrickLocation::TopRight)] = BrickState::All;
			_brickLocationToColliderMap[static_cast<size_t>(BrickLocation::TopRight)] = &_colliders.emplace_back(getAABBForBrickState(BrickLocation::TopRight, BrickState::All, _size), onCollisionCallbackTopRight);
			break;
		}
		case BrickWallType::BottomLeft: {
			_states[static_cast<size_t>(BrickLocation::BottomLeft)] = BrickState::All;
			_brickLocationToColliderMap[static_cast<size_t>(BrickLocation::BottomLeft)] = &_colliders.emplace_back(getAABBForBrickState(BrickLocation::BottomLeft, BrickState::All, _size), onCollisionCallbackBottomLeft);
			break;
		}
		case BrickWallType::BottomRight: {
			_states[static_cast<size_t>(BrickLocation::BottomRight)] = BrickState::All;
			_brickLocationToColliderMap[static_cast<size_t>(BrickLocation::BottomRight)] = &_colliders.emplace_back(getAABBForBrickState(BrickLocation::BottomRight, BrickState::All, _size), onCollisionCallbackBottomRight);
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

void BrickWall::renderBrick(const BrickLocation & location) const
{
	const size_t index = static_cast<size_t>(location);
	const auto state = _states[index];
	if (state != BrickState::Destroyed)
	{
		_sprites[static_cast<size_t>(state)]->render(_position + _offsets[index], _size / 2.0F, _rotation, _layer);
	}
}

void BrickWall::onCollisionCallback(const BrickLocation & brickLocation, const IGameObject & gameObject, const physics::CollisionDirection & collisionDirection)
{
	if (gameObject.gameObjectType() != GameObjectType::Bullet)
	{
		return;
	}
	const BrickState newBrickState = getBrickStateAfterCollision(_states[static_cast<size_t>(brickLocation)], collisionDirection);
	_states[static_cast<size_t>(brickLocation)] = newBrickState;

	if (newBrickState != BrickState::Destroyed)
	{
		_brickLocationToColliderMap[static_cast<size_t>(brickLocation)]->boundBox = getAABBForBrickState(brickLocation, newBrickState, _size);
	}
	else
	{
		_brickLocationToColliderMap[static_cast<size_t>(brickLocation)]->isActive = false;
	}
}

BrickWall::BrickState BrickWall::getBrickStateAfterCollision(const BrickState & brickState, const physics::CollisionDirection & collisionDirection)
{
	switch (brickState)
	{
		case BrickState::All: {
			switch (collisionDirection)
			{
				case physics::CollisionDirection::Up: {
					return BrickState::Bottom;
				}
				case physics::CollisionDirection::Down: {
					return BrickState::Top;
				}
				case physics::CollisionDirection::Left: {
					return BrickState::Right;
				}
				case physics::CollisionDirection::Right: {
					return BrickState::Left;
				}
			}
		}
		case BrickState::Top: {
			switch (collisionDirection)
			{
				case physics::CollisionDirection::Up: {
					return BrickState::Destroyed;
				}
				case physics::CollisionDirection::Down: {
					return BrickState::Destroyed;
				}
				case physics::CollisionDirection::Left: {
					return BrickState::TopRight;
				}
				case physics::CollisionDirection::Right: {
					return BrickState::TopLeft;
				}
			}
		}
		case BrickState::Bottom: {
			switch (collisionDirection)
			{
				case physics::CollisionDirection::Up: {
					return BrickState::Destroyed;
				}
				case physics::CollisionDirection::Down: {
					return BrickState::Destroyed;
				}
				case physics::CollisionDirection::Left: {
					return BrickState::BottomRight;
				}
				case physics::CollisionDirection::Right: {
					return BrickState::BottomLeft;
				}
			}
		}
		case BrickState::Left: {
			switch (collisionDirection)
			{
				case physics::CollisionDirection::Up: {
					return BrickState::BottomLeft;
				}
				case physics::CollisionDirection::Down: {
					return BrickState::TopLeft;
				}
				case physics::CollisionDirection::Left: {
					return BrickState::Destroyed;
				}
				case physics::CollisionDirection::Right: {
					return BrickState::Destroyed;
				}
			}
		}
		case BrickState::Right: {
			switch (collisionDirection)
			{
				case physics::CollisionDirection::Up: {
					return BrickState::BottomRight;
				}
				case physics::CollisionDirection::Down: {
					return BrickState::TopRight;
				}
				case physics::CollisionDirection::Left: {
					return BrickState::Destroyed;
				}
				case physics::CollisionDirection::Right: {
					return BrickState::Destroyed;
				}
			}
		}
		default: {
			return BrickState::Destroyed;
		}
	}
}

physics::AABB BrickWall::getAABBForBrickState(const BrickLocation & location, const BrickState & brickState, const glm::vec2 & size)
{
	glm::vec2 blockOffset(0);
	switch (location)
	{
		case BrickLocation::BottomLeft: {
			break;
		}
		case BrickLocation::BottomRight: {
			blockOffset.x += size.x / 2;
			break;
		}
		case BrickLocation::TopLeft: {
			blockOffset.y += size.y / 2;
			break;
		}
		case BrickLocation::TopRight: {
			blockOffset += size / 2.0f;
			break;
		}
	}

	glm::vec2 bottomLeft(0);
	glm::vec2 topRight(0);

	switch (brickState)
	{
		case BrickState::All: {
			topRight = glm::vec2(size.x / 2, size.y / 2);
			break;
		}
		case BrickState::TopLeft: {
			bottomLeft = glm::vec2(0, size.y / 4);
			topRight = glm::vec2(size.x / 4, size.y / 2);
			break;
		}
		case BrickState::TopRight: {
			bottomLeft = glm::vec2(size.x / 4, size.y / 4);
			topRight = glm::vec2(size.x / 2, size.y / 2);
			break;
		}
		case BrickState::Top: {
			bottomLeft = glm::vec2(0, size.y / 4);
			topRight = glm::vec2(size.x / 2, size.y / 2);
			break;
		}
		case BrickState::BottomLeft: {
			topRight = glm::vec2(size.x / 4, size.y / 4);
			break;
		}
		case BrickState::Left: {
			topRight = glm::vec2(size.x / 4, size.y / 2);
			break;
		}
		case BrickState::TopRight_BottomLeft: {
			topRight = glm::vec2(size.x / 2, size.y / 2);
			break;
		}
		case BrickState::Top_BottomLeft: {
			topRight = glm::vec2(size.x / 2, size.y / 2);
			break;
		}
		case BrickState::BottomRight: {
			bottomLeft = glm::vec2(size.x / 4, 0);
			topRight = glm::vec2(size.x / 2, size.y / 4);
			break;
		}
		case BrickState::TopLeft_BottomRight: {
			topRight = glm::vec2(size.x / 2, size.y / 2);
			break;
		}
		case BrickState::Right: {
			bottomLeft = glm::vec2(size.x / 4, 0);
			topRight = glm::vec2(size.x / 2, size.y / 2);
			break;
		}
		case BrickState::Top_BottomRight: {
			topRight = glm::vec2(size.x / 2, size.y / 2);
			break;
		}
		case BrickState::Bottom: {
			topRight = glm::vec2(size.x / 2, size.y / 4);
			break;
		}
		case BrickState::TopLeft_Bottom: {
			topRight = glm::vec2(size.x / 2, size.y / 2);
			break;
		}
		case BrickState::TopRight_Bottom: {
			topRight = glm::vec2(size.x / 2, size.y / 2);
			break;
		}
		case BrickState::Destroyed: {
			break;
		}
	}

	return {bottomLeft + blockOffset, topRight + blockOffset};
}
}// namespace game