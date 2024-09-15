#include "PhysicsEngine.hpp"
#include "../game/Level.hpp"
#include "../game/gameobjects/IGameObject.hpp"

namespace physics
{
inline CollisionDirection toDirection(const glm::vec2 & directionVec)
{
	CollisionDirection direction;
	if (directionVec.x > 0.0F)
	{
		direction = CollisionDirection::Right;
	}
	else if (directionVec.x < 0.0F)
	{
		direction = CollisionDirection::Left;
	}
	else if (directionVec.y > 0.0F)
	{
		direction = CollisionDirection::Up;
	}
	else if (directionVec.y < 0.0F)
	{
		direction = CollisionDirection::Down;
	}
	return direction;
}

PhysicsEngine::PhysicsEngine(PhysicsEngine && physicsEngine)
	: _dynamicGameObjects(std::move(physicsEngine._dynamicGameObjects))
{}

PhysicsEngine & PhysicsEngine::operator=(PhysicsEngine && physicsEngine)
{
	if (this == &physicsEngine)
	{
		return physicsEngine;
	}

	_dynamicGameObjects = std::move(physicsEngine._dynamicGameObjects);

	return *this;
}

void PhysicsEngine::update(const double delta)
{
	for (const auto & object: _dynamicGameObjects)
	{
		if (object->velocity() > 0.0)
		{
			const auto d = object->direction();
			{
				const auto p = object->position();
				if (d.x != 0)
				{
					object->position({p.x, (static_cast<int>(p.y / 4.0 + 0.5) * 4.0)});
				}
				else if (d.y != 0)
				{
					object->position({(static_cast<int>(p.x / 4.0 + 0.5) * 4.0), p.y});
				}
			}
			{
				const auto p = object->position();
				const auto v = object->velocity();
				const auto np = glm::vec2{p.x + delta * v * d.x, p.y + delta * v * d.y};

				const auto & colliders = object->colliders();
				auto objects = _currentLevel->objectsInArea(np, np + object->size());

				CollisionDirection objectDirection = toDirection(object->direction());
				CollisionDirection oppositeDirection = toDirection(-object->direction());

				bool hasCollision = false;
				for (const auto & objectCollider: colliders)
				{
					for (const auto & o: objects)
					{
						const auto & oColliders = o->colliders();
						if (o->colliders(object->gameObjectType()) && !oColliders.empty())
						{
							for (const auto & oCollider: oColliders)
							{
								if (oCollider.isActive && hasIntersection(np, objectCollider, o->position(), oCollider))
								{
									hasCollision = true;
									if (oCollider.onCollisionCallback)
									{
										oCollider.onCollisionCallback(*object, oppositeDirection);
									}
									if (objectCollider.onCollisionCallback)
									{
										objectCollider.onCollisionCallback(*o, objectDirection);
									}
								}
							}
						}
					}
				}

				if (!hasCollision)
				{
					object->position(np);
				}
			}
		}
	}
}

void PhysicsEngine::addDynamicObject(const std::shared_ptr<game::IGameObject> & dynamicObject)
{
	_dynamicGameObjects.insert(dynamicObject);
}

void PhysicsEngine::currentLevel(const std::shared_ptr<game::Level> & currentLevel)
{
	_currentLevel = currentLevel;
}

bool PhysicsEngine::hasIntersection(const glm::vec2 & position1, const Collider & collider1, const glm::vec2 & position2, const Collider & collider2)
{
	const auto bottomLeft1 = position1 + collider1.boundBox.bottomLeft;
	const auto topRight1 = position1 + collider1.boundBox.topRight;
	const auto bottomLeft2 = position2 + collider2.boundBox.bottomLeft;
	const auto topRight2 = position2 + collider2.boundBox.topRight;

	if (std::max(bottomLeft1.x, bottomLeft2.x) < std::min(topRight1.x, topRight2.x)
		&& std::max(bottomLeft1.y, bottomLeft2.y) < std::min(topRight1.y, topRight2.y))
	{
		return true;
	}

	return false;
}

bool hasIntersection(const glm::vec2 & position1, const Collider & collider1, const glm::vec2 & position2, const Collider & collider2)
{
	const glm::vec2 bottomLeft1 = collider1.boundBox.bottomLeft + position1;
	const glm::vec2 topRight1 = collider1.boundBox.topRight + position1;

	const glm::vec2 bottomLeft2 = collider2.boundBox.bottomLeft + position1;
	const glm::vec2 topRight2 = collider2.boundBox.topRight + position1;

	if (std::max(bottomLeft1.x, bottomLeft2.x) < std::min(topRight1.x, topRight2.x)
		&& std::max(bottomLeft1.y, bottomLeft2.y) < std::min(topRight1.y, topRight2.y))
	{
		return true;
	}

	return false;
}
}// namespace physics