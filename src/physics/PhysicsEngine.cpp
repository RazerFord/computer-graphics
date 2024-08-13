#include "PhysicsEngine.hpp"
#include "../game/Level.hpp"
#include "../game/gameobjects/IGameObject.hpp"
#include <iostream>

namespace physics
{
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
			const auto p = object->position();
			const auto d = object->direction();
			const auto v = object->velocity();
			const auto np = glm::vec2{p.x + delta * v * d.x, p.y + delta * v * d.y};

			const auto & colliders = object->colliders();
			auto objects = _currentLevel->objectsInArea(np, np + object->size());

			bool hasCollision = false;
			for (const auto & o: objects)
			{
				if (hasIntersection(np, colliders, o->position(), o->colliders()))
				{
					hasCollision = true;
					break;
				}
			}

			if (!hasCollision)
			{
				object->position(np);
			}
		}
	}
}

void PhysicsEngine::addDynamicObject(const std::shared_ptr<game::IGameObject> & dynamicObject)
{
	_dynamicGameObjects.push_back(dynamicObject);
}

void PhysicsEngine::currentLevel(const std::shared_ptr<game::Level> & currentLevel)
{
	_currentLevel = currentLevel;
}

bool PhysicsEngine::hasIntersection(const glm::vec2 & position1, const std::vector<AABB> & colliders1, const glm::vec2 & position2, const std::vector<AABB> & colliders2)
{
	for (const auto & collider1: colliders1)
	{
		const auto bottomLeft1 = position1 + collider1.bottomLeft;
		const auto topRight1 = position1 + collider1.topRight;
		for (const auto & collider2: colliders2)
		{
			const auto bottomLeft2 = position2 + collider2.bottomLeft;
			const auto topRight2 = position2 + collider2.topRight;

			if (std::max(bottomLeft1.x, bottomLeft2.x) < std::min(topRight1.x, topRight2.x)
				&& std::max(bottomLeft1.y, bottomLeft2.y) < std::min(topRight1.y, topRight2.y))
			{
				return true;
			}
		}
	}
	return false;
}

}// namespace physics