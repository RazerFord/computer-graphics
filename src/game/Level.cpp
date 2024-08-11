#include "Level.hpp"
#include "../resources/ResourceManager.hpp"
#include "gameobjects/BrickWall.hpp"
#include "gameobjects/IGameObject.hpp"
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
			return std::make_shared<game::BrickWall>(BrickWall::BrickWallType::Right, manager, position, size, rotation);
		}
		case '1': {
			return std::make_shared<game::BrickWall>(BrickWall::BrickWallType::Bottom, manager, position, size, rotation);
		}
		case '2': {
			return std::make_shared<game::BrickWall>(BrickWall::BrickWallType::Left, manager, position, size, rotation);
		}
		case '3': {
			return std::make_shared<game::BrickWall>(BrickWall::BrickWallType::Top, manager, position, size, rotation);
		}
		case '4': {
			return std::make_shared<game::BrickWall>(BrickWall::BrickWallType::All, manager, position, size, rotation);
		}
		case 'G': {
			return std::make_shared<game::BrickWall>(BrickWall::BrickWallType::BottomLeft, manager, position, size, rotation);
		}
		case 'H': {
			return std::make_shared<game::BrickWall>(BrickWall::BrickWallType::BottomRight, manager, position, size, rotation);
		}
		case 'I': {
			return std::make_shared<game::BrickWall>(BrickWall::BrickWallType::TopLeft, manager, position, size, rotation);
		}
		case 'J': {
			return std::make_shared<game::BrickWall>(BrickWall::BrickWallType::TopRight, manager, position, size, rotation);
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

	_gameObjects.reserve(_height * _width);
	int currentBottomOffset = BLOCK_SIZE * (_height - 1);

	for (const std::string & currentRow: description)
	{
		int currentLeftOffset = 0;
		for (const char currentElement: currentRow)
		{
			_gameObjects.emplace_back(makeGameObjectFromDescriptor(manager, currentElement, {currentLeftOffset, currentBottomOffset}, {BLOCK_SIZE, BLOCK_SIZE}, 0.0F));
			currentLeftOffset += BLOCK_SIZE;
		}
		currentBottomOffset -= BLOCK_SIZE;
	}
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
}// namespace game