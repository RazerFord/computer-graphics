#include "Game.hpp"
#include "../physics/PhysicsEngine.hpp"
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
	// _manager->getShader("spriteShader")->use();
	switch (_currentGameState)
	{
		case GameState::StartScreen: {
			if (_startScreen)
			{
				_startScreen->render();
			}
			break;
		}

		case GameState::Level: {
			if (_tank)
			{
				_tank->render();
			}
			if (_level)
			{
				_level->render();
			}
			break;
		}

		default: {
			throw std::runtime_error("non implemented case in render");
		}
	}
}

void Game::update(const double delta)
{
	switch (_currentGameState)
	{
		case GameState::StartScreen: {
			if (_keys[GLFW_KEY_ENTER])
			{
				_currentGameState = GameState::Level;
			}
			break;
		}

		case GameState::Level: {
			if (_level)
			{
				_level->update(delta);
			}

			if (_tank)
			{
				if (_keys[GLFW_KEY_W])
				{
					_tank->setOrientation(Orientation::Up);
					_tank->velocity(_tank->maxVelocity());
				}
				else if (_keys[GLFW_KEY_A])
				{
					_tank->setOrientation(Orientation::Left);
					_tank->velocity(_tank->maxVelocity());
				}
				else if (_keys[GLFW_KEY_D])
				{
					_tank->setOrientation(Orientation::Right);
					_tank->velocity(_tank->maxVelocity());
				}
				else if (_keys[GLFW_KEY_S])
				{
					_tank->setOrientation(Orientation::Down);
					_tank->velocity(_tank->maxVelocity());
				}
				else
				{
					_tank->velocity(0.0);
				}

				if (_keys[GLFW_KEY_SPACE])
				{
					_tank->fire();
				}

				_tank->update(delta);
			}
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

	auto program = _manager->getShader("spriteShader");

	_startScreen = std::make_shared<StartScreen>(_manager->startScreen(), *_manager);
	_level = std::make_shared<game::Level>(_manager->levels().back(), *_manager);

	_physicsEngine->currentLevel(_level);

	_tank = std::make_shared<game::Tank>(
		_manager->getSprite("player1_yellow_tank_type1_sprite_top"),
		_manager->getSprite("player1_yellow_tank_type1_sprite_right"),
		_manager->getSprite("player1_yellow_tank_type1_sprite_bottom"),
		_manager->getSprite("player1_yellow_tank_type1_sprite_left"),
		_physicsEngine,
		*_manager,
		0.05F,
		_level->getPlayerRespawn1(),
		glm::vec2(game::BLOCK_SIZE, game::BLOCK_SIZE),
		0.0F);

	_physicsEngine->addDynamicObject(_tank);

	_glfwWindowSize.x = _level->getStateWidth();
	_glfwWindowSize.y = _level->getStateHeight();

	glm::mat4 projection = glm::ortho(0.0F, static_cast<float>(_glfwWindowSize.x), 0.0F, static_cast<float>(_glfwWindowSize.y), -100.0F, 100.F);

	program->use();
	program->setInt("tex", 0);
	program->setMat4("projectionMat", projection);

	return true;
}

size_t Game::getCurrentWidth() const
{
	switch (_currentGameState)
	{
		case GameState::StartScreen: {
			return _startScreen->getStateWidth();
		}
		case GameState::Level: {
			return _level->getStateWidth();
		}
		default: {
			throw std::runtime_error("non implemented case in getCurrentWidth");
		}
	}
}

size_t Game::getCurrentHeight() const
{
	switch (_currentGameState)
	{
		case GameState::StartScreen: {
			return _startScreen->getStateHeight();
		}
		case GameState::Level: {
			return _level->getStateHeight();
		}
		default: {
			throw std::runtime_error("non implemented case in getCurrentHeigh");
		}
	}
}
}// namespace game