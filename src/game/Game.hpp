#pragma once

#include <array>
#include <glm/glm.hpp>
#include <memory>

namespace resources
{
class ResourceManager;
}

namespace game
{
class Game
{
private:
	std::shared_ptr<resources::ResourceManager> _manager;
	glm::ivec2 _glfwWindowSize;
    std::array<bool, 350> _keys;
	enum class GameState
	{
		Active,
		Pause,
	} _currentGameState;


public:
	Game(const std::shared_ptr<resources::ResourceManager> & manager, const glm::ivec2 glfwWindowSize);
	~Game();

	void render();
	void update(const size_t delta);
	void setKey(const int key, const int action);

	bool init();
};
}// namespace game