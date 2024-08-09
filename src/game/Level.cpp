#include "Level.hpp"
#include "../resources/ResourceManager.hpp"
#include "gameobjects/IGameObject.hpp"
#include <iostream>

namespace game
{
const int BLOCK_SIZE = 16;

Level::Level(const std::vector<std::string> & description, resources::ResourceManager * manager)
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
			switch (currentElement)
			{
				case '1': {
					break;
				}
			}
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