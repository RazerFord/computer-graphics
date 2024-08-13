#pragma once

#include <memory>
#include <vector>

namespace game
{
class IGameObject;
}

namespace physics
{
class PhysicsEngine
{
private:
	std::vector<std::shared_ptr<game::IGameObject>> _dynamicGameObjects;

public:
	PhysicsEngine() = default;
	PhysicsEngine(PhysicsEngine && physicsEngine);
	~PhysicsEngine() = default;

	PhysicsEngine & operator=(PhysicsEngine && physicsEngine);

	void update(const double delta);

	void addDynamicObject(const std::shared_ptr<game::IGameObject> & dynamicObject);
};
}// namespace physics