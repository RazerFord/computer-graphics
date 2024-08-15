#pragma once

#include <glm/vec2.hpp>
#include <memory>
#include <unordered_set>
#include <vector>

namespace game
{
class IGameObject;
class Level;
}// namespace game

namespace physics
{
struct AABB {
	glm::vec2 bottomLeft;
	glm::vec2 topRight;
};

class PhysicsEngine
{
private:
	std::unordered_set<std::shared_ptr<game::IGameObject>> _dynamicGameObjects;
	std::shared_ptr<game::Level> _currentLevel;

public:
	PhysicsEngine() = default;
	PhysicsEngine(PhysicsEngine && physicsEngine);
	~PhysicsEngine() = default;

	PhysicsEngine & operator=(PhysicsEngine && physicsEngine);

	void update(const double delta);

	void addDynamicObject(const std::shared_ptr<game::IGameObject> & dynamicObject);

	void currentLevel(const std::shared_ptr<game::Level> & currentLevel);

private:
	bool hasIntersection(const glm::vec2 & position1, const std::vector<AABB> & colliders1, const glm::vec2 & position2, const std::vector<AABB> & colliders2);
};
}// namespace physics