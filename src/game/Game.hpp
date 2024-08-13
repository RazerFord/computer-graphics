#pragma once

#include <array>
#include <glm/glm.hpp>
#include <memory>

namespace resources
{
class ResourceManager;
}

namespace physics
{
class PhysicsEngine;
}

namespace game
{
class Tank;
class Level;

class Game
{
private:
	std::shared_ptr<resources::ResourceManager> _manager;
	std::shared_ptr<physics::PhysicsEngine> _physicsEngine;
	glm::ivec2 _glfwWindowSize;
	std::array<bool, 350> _keys;
	enum class GameState
	{
		Active,
		Pause,
	} _currentGameState;

	std::shared_ptr<Tank> _tank;
	std::shared_ptr<Level> _level;

public:
	Game(const std::shared_ptr<resources::ResourceManager> & manager, const std::shared_ptr<physics::PhysicsEngine> & _physicsEngine, const glm::ivec2 glfwWindowSize);
	~Game();

	void render();
	void update(const double delta);
	void setKey(const int key, const int action);

	bool init();

	size_t getCurrentLevelWidth() const;
	size_t getCurrentLevelHeight() const;
};
}// namespace game