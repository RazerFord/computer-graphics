#include "PhysicsEngine.hpp"
#include "../game/gameobjects/IGameObject.hpp"

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

			object->position({p.x + delta * v * d.x, p.y + delta * v * d.y});
		}
	}
}

void PhysicsEngine::addDynamicObject(const std::shared_ptr<game::IGameObject> & dynamicObject)
{
	_dynamicGameObjects.push_back(dynamicObject);
}
}// namespace physics