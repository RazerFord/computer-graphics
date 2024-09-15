#pragma once

#include <functional>
#include <glm/vec2.hpp>
#include <memory>
#include <unordered_set>

namespace game
{
class IGameObject;
class Level;
}// namespace game

namespace physics
{
enum class CollisionDirection
{
	Up,
	Down,
	Left,
	Right,
};

struct AABB {
	glm::vec2 bottomLeft;
	glm::vec2 topRight;
};

struct Collider {
	AABB boundBox;
	bool isActive;
	std::function<void(const game::IGameObject &, const CollisionDirection &)> onCollisionCallback;

	Collider(const glm::vec2 & bottomLeft, const glm::vec2 & topRight, const std::function<void(const game::IGameObject &, const CollisionDirection &)> & onCollisionCallback)
		: boundBox{bottomLeft, topRight}
		, isActive(true)
		, onCollisionCallback(onCollisionCallback)
	{}

	Collider(const AABB & boundBox, const std::function<void(const game::IGameObject &, const CollisionDirection &)> & onCollisionCallback)
		: boundBox(boundBox)
		, isActive(true)
		, onCollisionCallback(onCollisionCallback)
	{}
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
	bool hasIntersection(const glm::vec2 & position1, const Collider & collider1, const glm::vec2 & position2, const Collider & collider2);
};
}// namespace physics