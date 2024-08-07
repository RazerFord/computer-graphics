#include "Game.hpp"
#include "../render/AnimatedSprite.hpp"
#include "../render/ShaderProgram.hpp"
#include "../resources/ResourceManager.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/glm.hpp>
#include <iostream>

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
	_manager->getAnimatedSprite("sprite")->render();
}

void Game::update(const size_t delta)
{
	_manager->getAnimatedSprite("sprite")->update(delta);
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

	render::AnimatedSprite::States states{{"first", 50}, {"second", 50}, {"third", 50}, {"four", 50}};
	sprite->insertState("example", states);
	sprite->setState("example");
	sprite->setPosition(glm::vec2(100.0F, 100.0F));

	glm::mat4 projection = glm::ortho(0.0F, static_cast<float>(_glfwWindowSize.x), 0.0F, static_cast<float>(_glfwWindowSize.y), -100.0F, 100.F);

	program->use();
	program->setInt("tex", 0);
	program->setMat4("projectionMat", projection);

	return true;
}
}// namespace game