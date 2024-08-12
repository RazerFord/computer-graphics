#include "Level.hpp"
#include "../resources/ResourceManager.hpp"
#include "gameobjects/Border.hpp"
#include "gameobjects/BrickWall.hpp"
#include "gameobjects/ConcreteWall.hpp"
#include "gameobjects/Eagle.hpp"
#include "gameobjects/IGameObject.hpp"
#include "gameobjects/Ice.hpp"
#include "gameobjects/Trees.hpp"
#include "gameobjects/Water.hpp"
#include <iostream>
#include <memory>

namespace game
{
const int BLOCK_SIZE = 16;

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

Level::Level(const std::vector<std::string> & description, const resources::ResourceManager & manager)
{
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

	for (const std::string & currentRow: description)
	{
		int currentLeftOffset = BLOCK_SIZE;
		for (const char currentElement: currentRow)
		{
			_gameObjects.emplace_back(makeGameObjectFromDescriptor(manager, currentElement, {currentLeftOffset, currentBottomOffset}, {BLOCK_SIZE, BLOCK_SIZE}, 0.0F));
			currentLeftOffset += BLOCK_SIZE;
		}
		currentBottomOffset -= BLOCK_SIZE;
	}

	// border bottom
	_gameObjects.emplace_back(std::make_shared<game::Border>(manager, glm::vec2{BLOCK_SIZE, 0.0F}, glm::vec2{_width * BLOCK_SIZE, BLOCK_SIZE / 2.0F}, 0.0F, 0.0F));
	// border top
	_gameObjects.emplace_back(std::make_shared<game::Border>(manager, glm::vec2{BLOCK_SIZE, _height * BLOCK_SIZE + BLOCK_SIZE / 2.0F}, glm::vec2{_width * BLOCK_SIZE, BLOCK_SIZE / 2.0F}, 0.0F, 0.0F));
	// border left
	_gameObjects.emplace_back(std::make_shared<game::Border>(manager, glm::vec2{0.0F, 0.0F}, glm::vec2{BLOCK_SIZE, (_height + 1) * BLOCK_SIZE}, 0.0F, 0.0F));
	// border right
	_gameObjects.emplace_back(std::make_shared<game::Border>(manager, glm::vec2{(_width + 1) * BLOCK_SIZE, 0.0F}, glm::vec2{2 * BLOCK_SIZE, (_height + 1) * BLOCK_SIZE}, 0.0F, 0.0F));
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
}

void Level::update(const size_t delta)
{
	for (const auto & gameObject: _gameObjects)
	{
		if (gameObject)
		{
			gameObject->update(delta);
		}
	}
}

size_t Level::getLevelWidth() const
{
	return (_width + 3) * BLOCK_SIZE;
}

size_t Level::getLevelHeight() const
{
	return (_height + 1) * BLOCK_SIZE;
}
}// namespace game