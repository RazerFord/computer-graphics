#include "Game.hpp"
#include "../render/ShaderProgram.hpp"
#include "../resources/ResourceManager.hpp"
#include "Level.hpp"
#include "gameobjects/Tank.hpp"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/glm.hpp>
#include <memory>

namespace game
{

Game::Game(const std::shared_ptr<resources::ResourceManager> & manager, const glm::ivec2 glfwWindowSize)
	: _manager(manager)
	, _glfwWindowSize(glfwWindowSize)
	, _currentGameState(GameState::Active)
{
	_keys.fill(false);
	init();
}

Game::~Game() {}

void Game::render()
{
	_manager->getShader("spriteShader")->use();
	_tank->render();
	_level->render();
}

void Game::update(const size_t delta)
{
	_level->update(delta);

	if (_keys[GLFW_KEY_W])
	{
		_tank->setOrientation(Orientation::Up);
		_tank->setMove(true);
	}
	else if (_keys[GLFW_KEY_A])
	{
		_tank->setOrientation(Orientation::Left);
		_tank->setMove(true);
	}
	else if (_keys[GLFW_KEY_D])
	{
		_tank->setOrientation(Orientation::Right);
		_tank->setMove(true);
	}
	else if (_keys[GLFW_KEY_S])
	{
		_tank->setOrientation(Orientation::Down);
		_tank->setMove(true);
	}
	else
	{
		_tank->setMove(false);
	}

	_tank->update(delta);
}

void Game::setKey(const int key, const int action)
{
	_keys[key] = action;
}

bool Game::init()
{
	_manager->loadJSON("resources.json");

	auto program = _manager->getShader("spriteShader");
	auto tankAnimatedSprite = _manager->getAnimatedSprite("tankSprite");

	_tank = std::make_unique<game::Tank>(tankAnimatedSprite, 0.1F, glm::vec2(0.0F, 0.0F), glm::vec2(16.0F, 16.0F));
	_level = std::make_unique<game::Level>(_manager->levels().front(), *_manager);

	glm::mat4 projection = glm::ortho(0.0F, static_cast<float>(_glfwWindowSize.x), 0.0F, static_cast<float>(_glfwWindowSize.y), -100.0F, 100.F);

	program->use();
	program->setInt("tex", 0);
	program->setMat4("projectionMat", projection);

	return true;
}
}// namespace game