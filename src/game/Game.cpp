#include "Game.hpp"
#include "../physics/PhysicsEngine.hpp"
#include "../render/Render.hpp"
#include "../render/ShaderProgram.hpp"
#include "../resources/ResourceManager.hpp"
#include "gameobjects/Tank.hpp"
#include "gamestates/Level.hpp"
#include "gamestates/StartScreen.hpp"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/glm.hpp>
#include <memory>
#include <stdexcept>

namespace game
{

Game::Game(const std::shared_ptr<resources::ResourceManager> & manager, const std::shared_ptr<physics::PhysicsEngine> & physicsEngine, const glm::ivec2 glfwWindowSize)
	: _manager(manager)
	, _physicsEngine(physicsEngine)
	, _glfwWindowSize(glfwWindowSize)
	, _currentGameState(GameState::StartScreen)
{
	_keys.fill(false);
	init();
}

Game::~Game() {}

void Game::render()
{
	_gameState->render();
}

void Game::update(const double delta)
{
	switch (_currentGameState)
	{
		case GameState::StartScreen: {
			if (_keys[GLFW_KEY_ENTER])
			{
				_currentGameState = GameState::Level;
				startNewLevel(1);
			}
			break;
		}

		case GameState::Level: {
			_gameState->processInput(_keys);
			_gameState->update(delta);
			_physicsEngine->update(delta);
			break;
		}

		default: {
			throw std::runtime_error("non implemented case in update");
		}
	}
}

void Game::setKey(const int key, const int action)
{
	_keys[key] = action;
}

bool Game::init()
{
	_manager->loadJSON("resources.json");
	_program = _manager->getShader("spriteShader");
	_program->use();
	_program->setInt("tex", 0);
	_gameState = std::make_shared<StartScreen>(_manager->startScreen(), *_manager);
	setWindowSize(_glfwWindowSize);
	return true;
}

size_t Game::getCurrentWidth() const
{
	return _gameState->getStateWidth();
}

size_t Game::getCurrentHeight() const
{
	return _gameState->getStateHeight();
}

void Game::startNewLevel(const size_t level)
{
	auto spLevel = std::make_shared<game::Level>(_manager->levels()[level], _manager, _physicsEngine);
	_gameState = spLevel;
	_physicsEngine->currentLevel(spLevel);
	updateViewport();
}

void Game::setWindowSize(const glm::vec2 & windowSize)
{
	_glfwWindowSize = windowSize;
	updateViewport();
}

void Game::updateViewport()
{
	const float aspectRation = static_cast<float>(getCurrentWidth()) / getCurrentHeight();
	int viewportWidth = _glfwWindowSize.x;
	int viewportHeight = _glfwWindowSize.y;
	int leftOffset = 0;
	int bottomOffset = 0;

	if (static_cast<float>(_glfwWindowSize.x) / _glfwWindowSize.y > aspectRation)
	{
		viewportWidth = _glfwWindowSize.y * aspectRation;
		leftOffset = (_glfwWindowSize.x - viewportWidth) / 2;
	}
	else if (static_cast<float>(_glfwWindowSize.x) / _glfwWindowSize.y < aspectRation)
	{
		viewportHeight = _glfwWindowSize.x / aspectRation;
		bottomOffset = (_glfwWindowSize.y - viewportHeight) / 2;
	}

	render::Render::setViewport(viewportWidth, viewportHeight, leftOffset, bottomOffset);

	glm::mat4 projection = glm::ortho(0.0F, static_cast<float>(getCurrentWidth()), 0.0F, static_cast<float>(getCurrentHeight()), -100.0F, 100.F);
	_program->setMat4("projectionMat", projection);
}
}// namespace game