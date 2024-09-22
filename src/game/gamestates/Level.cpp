#include "Level.hpp"
#include "../../resources/ResourceManager.hpp"
#include "../gameobjects/Border.hpp"
#include "../gameobjects/BrickWall.hpp"
#include "../gameobjects/ConcreteWall.hpp"
#include "../gameobjects/Eagle.hpp"
#include "../gameobjects/IGameObject.hpp"
#include "../gameobjects/Ice.hpp"
#include "../gameobjects/Tank.hpp"
#include "../gameobjects/Trees.hpp"
#include "../gameobjects/Water.hpp"
#include "GLFW/glfw3.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>

namespace game
{
std::shared_ptr<IGameObject> makeGameObjectFromDescriptor(const resources::ResourceManager & manager,
														  const char descriptor,
														  const glm::vec2 & position,
														  const glm::vec2 & size,
														  const float rotation)
{
	switch (descriptor)
	{
		case '0': {
			return std::make_shared<game::BrickWall>(BrickWall::BrickWallType::Right, manager, position, size, rotation, 0.0F);
		}
		case '1': {
			return std::make_shared<game::BrickWall>(BrickWall::BrickWallType::Bottom, manager, position, size, rotation, 0.0F);
		}
		case '2': {
			return std::make_shared<game::BrickWall>(BrickWall::BrickWallType::Left, manager, position, size, rotation, 0.0F);
		}
		case '3': {
			return std::make_shared<game::BrickWall>(BrickWall::BrickWallType::Top, manager, position, size, rotation, 0.0F);
		}
		case '4': {
			return std::make_shared<game::BrickWall>(BrickWall::BrickWallType::All, manager, position, size, rotation, 0.0F);
		}
		case '5': {
			return std::make_shared<game::ConcreteWall>(ConcreteWall::ConcreteWallType::Right, manager, position, size, rotation, 0.0F);
		}
		case '6': {
			return std::make_shared<game::ConcreteWall>(ConcreteWall::ConcreteWallType::Bottom, manager, position, size, rotation, 0.0F);
		}
		case '7': {
			return std::make_shared<game::ConcreteWall>(ConcreteWall::ConcreteWallType::Left, manager, position, size, rotation, 0.0F);
		}
		case '8': {
			return std::make_shared<game::ConcreteWall>(ConcreteWall::ConcreteWallType::Top, manager, position, size, rotation, 0.0F);
		}
		case '9': {
			return std::make_shared<game::ConcreteWall>(ConcreteWall::ConcreteWallType::All, manager, position, size, rotation, 0.0F);
		}
		case 'A': {
			return std::make_shared<game::Water>(manager, position, size, rotation, 0.0F);
		}
		case 'B': {
			return std::make_shared<game::Trees>(manager, position, size, rotation, 1.0F);
		}
		case 'C': {
			return std::make_shared<game::Ice>(manager, position, size, rotation, -1.0F);
		}
		case 'E': {
			return std::make_shared<game::Eagle>(manager, position, size, rotation, 0.0F);
		}
		case 'G': {
			return std::make_shared<game::BrickWall>(BrickWall::BrickWallType::BottomLeft, manager, position, size, rotation, 0.0F);
		}
		case 'H': {
			return std::make_shared<game::BrickWall>(BrickWall::BrickWallType::BottomRight, manager, position, size, rotation, 0.0F);
		}
		case 'I': {
			return std::make_shared<game::BrickWall>(BrickWall::BrickWallType::TopLeft, manager, position, size, rotation, 0.0F);
		}
		case 'J': {
			return std::make_shared<game::BrickWall>(BrickWall::BrickWallType::TopRight, manager, position, size, rotation, 0.0F);
		}
		case 'D': {
			return nullptr;
		}
		default: {
			std::cerr << "unknown game object descriptor \"" << descriptor << "\"" << std::endl;
			return nullptr;
		}
	}
}

Level::Level(
	const std::vector<std::string> & description,
	const std::shared_ptr<resources::ResourceManager> & manager,
	const std::shared_ptr<physics::PhysicsEngine> & physicsEngine)
{
	_manager = manager;
	_physicsEngine = physicsEngine;

	if (description.empty())
	{
		std::cerr << "empty level description" << std::endl;
		return;
	}
	_height = description.size();
	_width = description[0].size();

	// +4 for border
	_gameObjects.reserve(_height * _width + 4);
	int currentBottomOffset = BLOCK_SIZE * (_height - 1) + BLOCK_SIZE / 2;

	_playerRespawn1 = {BLOCK_SIZE * (_width / 2 - 1), BLOCK_SIZE / 2};
	_playerRespawn2 = {BLOCK_SIZE * (_width / 2 + 3), BLOCK_SIZE / 2};
	_enemyRespawn1 = {BLOCK_SIZE, BLOCK_SIZE * _height - BLOCK_SIZE / 2};
	_enemyRespawn1 = {BLOCK_SIZE * (_width + 1), BLOCK_SIZE * _height - BLOCK_SIZE / 2};
	_enemyRespawn1 = {BLOCK_SIZE * _width, BLOCK_SIZE * _height - BLOCK_SIZE / 2};

	for (const std::string & currentRow: description)
	{
		int currentLeftOffset = BLOCK_SIZE;
		for (const char currentElement: currentRow)
		{
			switch (currentElement)
			{
				case 'K': {
					_playerRespawn1 = {currentLeftOffset, currentBottomOffset};
				}
				case 'L': {
					_playerRespawn2 = {currentLeftOffset, currentBottomOffset};
				}
				case 'M': {
					_enemyRespawn1 = {currentLeftOffset, currentBottomOffset};
				}
				case 'N': {
					_enemyRespawn2 = {currentLeftOffset, currentBottomOffset};
				}
				case 'O': {
					_enemyRespawn3 = {currentLeftOffset, currentBottomOffset};
				}
				default: {
					_gameObjects.emplace_back(makeGameObjectFromDescriptor(*manager, currentElement, {currentLeftOffset, currentBottomOffset}, {BLOCK_SIZE, BLOCK_SIZE}, 0.0F));
				}
			}
			currentLeftOffset += BLOCK_SIZE;
		}
		currentBottomOffset -= BLOCK_SIZE;
	}

	// border bottom
	_gameObjects.emplace_back(std::make_shared<game::Border>(*_manager, glm::vec2{BLOCK_SIZE, 0.0F}, glm::vec2{_width * BLOCK_SIZE, BLOCK_SIZE / 2.0F}, 0.0F, 0.0F));
	// border top
	_gameObjects.emplace_back(std::make_shared<game::Border>(*_manager, glm::vec2{BLOCK_SIZE, _height * BLOCK_SIZE + BLOCK_SIZE / 2.0F}, glm::vec2{_width * BLOCK_SIZE, BLOCK_SIZE / 2.0F}, 0.0F, 0.0F));
	// border left
	_gameObjects.emplace_back(std::make_shared<game::Border>(*_manager, glm::vec2{0.0F, 0.0F}, glm::vec2{BLOCK_SIZE, (_height + 1) * BLOCK_SIZE}, 0.0F, 0.0F));
	// border right
	_gameObjects.emplace_back(std::make_shared<game::Border>(*_manager, glm::vec2{(_width + 1) * BLOCK_SIZE, 0.0F}, glm::vec2{2 * BLOCK_SIZE, (_height + 1) * BLOCK_SIZE}, 0.0F, 0.0F));
}

void Level::render() const
{
	for (const auto & gameObject: _gameObjects)
	{
		if (gameObject)
		{
			gameObject->render();
		}
	}

	_tank->render();
}

void Level::update(const double delta)
{
	for (const auto & gameObject: _gameObjects)
	{
		if (gameObject)
		{
			gameObject->update(delta);
		}
	}

	_tank->update(delta);
}

int Level::getStateWidth() const
{
	return (_width + 3) * BLOCK_SIZE;
}

int Level::getStateHeight() const
{
	return (_height + 1) * BLOCK_SIZE;
}

void Level::processInput(const std::array<bool, 350> & keys)
{
	if (keys[GLFW_KEY_W])
	{
		_tank->setOrientation(Orientation::Up);
		_tank->velocity(_tank->maxVelocity());
	}
	else if (keys[GLFW_KEY_A])
	{
		_tank->setOrientation(Orientation::Left);
		_tank->velocity(_tank->maxVelocity());
	}
	else if (keys[GLFW_KEY_D])
	{
		_tank->setOrientation(Orientation::Right);
		_tank->velocity(_tank->maxVelocity());
	}
	else if (keys[GLFW_KEY_S])
	{
		_tank->setOrientation(Orientation::Down);
		_tank->velocity(_tank->maxVelocity());
	}
	else
	{
		_tank->velocity(0.0);
	}

	if (keys[GLFW_KEY_SPACE])
	{
		_tank->fire();
	}
}

const glm::ivec2 Level::getPlayerRespawn1() const
{
	return _playerRespawn1;
}

const glm::ivec2 Level::getPlayerRespawn2() const
{
	return _playerRespawn2;
}

const glm::ivec2 Level::getEnemyRespawn1() const
{
	return _enemyRespawn1;
}

const glm::ivec2 Level::getEnemyRespawn2() const
{
	return _enemyRespawn2;
}

const glm::ivec2 Level::getEnemyRespawn3() const
{
	return _enemyRespawn3;
}

void Level::initPhysics()
{
	_tank = std::make_shared<game::Tank>(
		_manager->getSprite("player1_yellow_tank_type1_sprite_top"),
		_manager->getSprite("player1_yellow_tank_type1_sprite_right"),
		_manager->getSprite("player1_yellow_tank_type1_sprite_bottom"),
		_manager->getSprite("player1_yellow_tank_type1_sprite_left"),
		_physicsEngine,
		*_manager,
		0.05F,
		getPlayerRespawn1(),
		glm::vec2(game::BLOCK_SIZE, game::BLOCK_SIZE),
		0.0F);

	_physicsEngine->addDynamicObject(_tank);
}


std::vector<std::shared_ptr<IGameObject>> Level::objectsInArea(const glm::vec2 & bottomLeft, const glm::vec2 & topRight) const
{
	std::vector<std::shared_ptr<IGameObject>> objects;

	glm::vec2 bottomLeftConverted(std::clamp(bottomLeft.x - BLOCK_SIZE, 0.0F, static_cast<float>(_width * BLOCK_SIZE)),
								  std::clamp(_height * BLOCK_SIZE - bottomLeft.y + BLOCK_SIZE / 2.0F, 0.0F, static_cast<float>(_height * BLOCK_SIZE)));
	glm::vec2 topRightConverted(std::clamp(topRight.x - BLOCK_SIZE, 0.0F, static_cast<float>(_width * BLOCK_SIZE)),
								std::clamp(_height * BLOCK_SIZE - topRight.y + BLOCK_SIZE / 2.0F, 0.0F, static_cast<float>(_height * BLOCK_SIZE)));

	size_t startX = std::floor(bottomLeftConverted.x / BLOCK_SIZE);
	size_t endX = std::ceil(topRightConverted.x / BLOCK_SIZE);

	size_t startY = std::floor(topRightConverted.y / BLOCK_SIZE);
	size_t endY = std::ceil(bottomLeftConverted.y / BLOCK_SIZE);

	for (size_t j = startY; j < endY; j++)
	{
		for (size_t i = startX; i < endX; i++)
		{
			auto & currentObject = _gameObjects[j * _width + i];
			if (currentObject)
			{
				objects.push_back(currentObject);
			}
		}
	}

	if (endX >= _width)
	{
		objects.emplace_back(_gameObjects[_gameObjects.size() - 1]);
	}
	if (startX < 1)
	{
		objects.emplace_back(_gameObjects[_gameObjects.size() - 2]);
	}
	if (startY < 1)
	{
		objects.emplace_back(_gameObjects[_gameObjects.size() - 3]);
	}
	if (endY >= _height)
	{
		objects.emplace_back(_gameObjects[_gameObjects.size() - 4]);
	}

	return objects;
}
}// namespace game