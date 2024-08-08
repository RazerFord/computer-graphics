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
	_manager->getAnimatedSprite("sprite")->render();
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
	auto program = _manager->loadShader("triangle", "shaders/vsprite.vs", "shaders/fsprite.fs");
	if (!program)
	{
		std::cerr << "can't create shader program \"" << "triangle" << "\"" << std::endl;
		return false;
	}

	auto texture = _manager->loadTexture("firsttexture", "textures/firsttexture.jpg");
	if (!texture)
	{
		std::cerr << "can't create texture \"" << "firsttexture" << "\"" << std::endl;
		return false;
	}

	auto atlas = _manager->loadTextureAtlas("firsttexture", "textures/firsttexture.jpg", {"first", "second", "third", "four"}, 64, 64);
	if (!atlas)
	{
		std::cerr << "can't create texture atlas \"" << "firsttexture" << "\"" << std::endl;
		return false;
	}

	auto sprite = _manager->loadAnimatedSprite("sprite", "triangle", "firsttexture", 100.0F, 100.0F);
	if (!sprite)
	{
		std::cerr << "can't create sprite \"" << "sprite" << "\"" << std::endl;
		return false;
	}

	std::vector<std::string> tankSubTexturesName{"tankUp1", "tankUp2", "tankLeft1", "tankLeft2", "tankDown1", "tankDown2", "tankRight1", "tankRight2"};

	auto battleCityAtlas = _manager->loadTextureAtlas("battleCity", "textures/battlecity.png", tankSubTexturesName, 16, 16);
	if (!battleCityAtlas)
	{
		std::cerr << "can't create texture atlas \"" << "battleCity" << "\"" << std::endl;
		return false;
	}

	auto tankAnimatedSprite = _manager->loadAnimatedSprite("tankSprite", "triangle", "battleCity", 200, 200, "tankUp1");
	if (!tankAnimatedSprite)
	{
		std::cerr << "can't create sprite \"" << "tankSprite" << "\"" << std::endl;
		return false;
	}

	render::AnimatedSprite::States tankUpState{{"tankUp1", 100}, {"tankUp2", 100}};
	render::AnimatedSprite::States tankLeftState{{"tankLeft1", 100}, {"tankLeft2", 100}};
	render::AnimatedSprite::States tankDownState{{"tankDown1", 100}, {"tankDown2", 100}};
	render::AnimatedSprite::States tankRightState{{"tankRight1", 100}, {"tankRight2", 100}};
	tankAnimatedSprite->insertState("tankUpState", tankUpState);
	tankAnimatedSprite->insertState("tankLeftState", tankLeftState);
	tankAnimatedSprite->insertState("tankDownState", tankDownState);
	tankAnimatedSprite->insertState("tankRightState", tankRightState);
	tankAnimatedSprite->setState("tankUpState");

	_tank = std::make_unique<game::Tank>(tankAnimatedSprite, 0.1F, glm::vec2(200.0F, 250.0F));

	glm::mat4 projection = glm::ortho(0.0F, static_cast<float>(_glfwWindowSize.x), 0.0F, static_cast<float>(_glfwWindowSize.y), -100.0F, 100.F);

	program->use();
	program->setInt("tex", 0);
	program->setMat4("projectionMat", projection);

	return true;
}
}// namespace game