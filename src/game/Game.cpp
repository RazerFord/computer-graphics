#include "Game.hpp"
#include "../render/AnimatedSprite.hpp"
#include "../render/ShaderProgram.hpp"
#include "../resources/ResourceManager.hpp"
#include "Tank.hpp"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <memory>
#include <vector>

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
	_manager->getShader("triangle")->use();
	_tank->render();
}

void Game::update(const size_t delta)
{
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

	auto program = _manager->getShader("triangle");
	auto tankAnimatedSprite = _manager->getAnimatedSprite("tankSprite");

	_tank = std::make_unique<game::Tank>(tankAnimatedSprite, 0.1F, glm::vec2(200.0F, 250.0F));

	glm::mat4 projection = glm::ortho(0.0F, static_cast<float>(_glfwWindowSize.x), 0.0F, static_cast<float>(_glfwWindowSize.y), -100.0F, 100.F);

	program->use();
	program->setInt("tex", 0);
	program->setMat4("projectionMat", projection);

	return true;
}
}// namespace game