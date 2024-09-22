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
class StartScreen;

class Game
{
private:
	std::shared_ptr<resources::ResourceManager> _manager;
	std::shared_ptr<physics::PhysicsEngine> _physicsEngine;
	glm::ivec2 _glfwWindowSize;
	enum class GameState
	{
		StartScreen,
		LevelStart,
		Level,
		Pause,
		Scores,
		GameOver,
	} _currentGameState;
	std::array<bool, 350> _keys;

	std::shared_ptr<Tank> _tank;
	std::shared_ptr<Level> _level;

	std::shared_ptr<game::StartScreen> _startScreen;

public:
	Game(const std::shared_ptr<resources::ResourceManager> & manager, const std::shared_ptr<physics::PhysicsEngine> & _physicsEngine, const glm::ivec2 glfwWindowSize);
	~Game();

	void render();
	void update(const double delta);
	void setKey(const int key, const int action);

	bool init();

	size_t getCurrentWidth() const;
	size_t getCurrentHeight() const;
};
}// namespace game