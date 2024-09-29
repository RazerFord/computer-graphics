#include "StartScreen.hpp"

#include "../../render/Sprite.hpp"
#include "../../resources/ResourceManager.hpp"
#include "../Game.hpp"
#include "GLFW/glfw3.h"
#include <iostream>

namespace
{
inline std::shared_ptr<render::Sprite> getSpriteForDescription(const char description, const resources::ResourceManager & manager)
{
	switch (description)
	{
		case '0':
			return manager.getSprite("brickWall_All");
		case '1':
			return manager.getSprite("brickWall_TopLeft");
		case '2':
			return manager.getSprite("brickWall_TopRight");
		case '3':
			return manager.getSprite("brickWall_Top");
		case '4':
			return manager.getSprite("brickWall_BottomLeft");
		case '5':
			return manager.getSprite("brickWall_Left");
		case '6':
			return manager.getSprite("brickWall_TopRight_BottomLeft");
		case '7':
			return manager.getSprite("brickWall_Top_BottomLeft");
		case '8':
			return manager.getSprite("brickWall_BottomRight");
		case '9':
			return manager.getSprite("brickWall_TopLeft_BottomRight");
		case 'A':
			return manager.getSprite("brickWall_Right");
		case 'B':
			return manager.getSprite("brickWall_Top_BottomRight");
		case 'C':
			return manager.getSprite("brickWall_Bottom");
		case 'D':
			return manager.getSprite("brickWall_TopLeft_Bottom");
		case 'E':
			return manager.getSprite("brickWall_TopRight_Bottom");
		case 'F':
			return nullptr;
		default:
			std::cerr << "Unknown Start Level description: " << description << std::endl;
	}
	return nullptr;
}
}// namespace

namespace game
{
StartScreen::StartScreen(const std::vector<std::string> & startScreenDescription, const resources::ResourceManager & manager, Game * game)
	: _keyReleased(true)
	, _game(game)
	, _currentMenuSelect(0)
	, _menu(manager.getSprite("menu"), glm::vec2(11 * BLOCK_SIZE, START_SCREEN_HEIGHT - startScreenDescription.size() * BLOCK_SIZE - MENU_HEIGHT - 5 * BLOCK_SIZE))
	, _tank(manager.getSprite("player1_yellow_tank_type1_sprite_right"), glm::vec2(8 * BLOCK_SIZE, _menu.second.y + 6 * BLOCK_SIZE - _currentMenuSelect * 2 * BLOCK_SIZE))
	, _tankAnimator(_tank.first)
{
	if (startScreenDescription.empty())
	{
		std::cerr << "Empty start screen description" << std::endl;
	}
	auto leftOffsetPixels = 4 * BLOCK_SIZE;
	auto bottomOffsetPixels = START_SCREEN_HEIGHT - 4 * BLOCK_SIZE;

	auto currentBottomOffset = bottomOffsetPixels;
	for (const std::string & currentRow: startScreenDescription)
	{
		int currentLeftOffset = leftOffsetPixels;
		for (const char currentElement: currentRow)
		{
			auto sprite = getSpriteForDescription(currentElement, manager);
			_sprites.emplace_back(std::make_pair(sprite, glm::vec2(currentLeftOffset, currentBottomOffset)));
			currentLeftOffset += BLOCK_SIZE;
		}
		currentBottomOffset -= BLOCK_SIZE;
	}
}

void StartScreen::render() const
{
	for (const auto & current: _sprites)
	{
		if (current.first)
		{
			current.first->render(current.second, glm::vec2(BLOCK_SIZE), 0.F);
		}
	}
	_menu.first->render(_menu.second, glm::vec2(MENU_WIDTH, MENU_HEIGHT), 0.F);
	_tank.first->render(glm::vec2(_tank.second.x, _tank.second.y - _currentMenuSelect * 2 * BLOCK_SIZE), glm::vec2(TANK_SIZE), 0.F, 0.F, _tankAnimator.getCurrentFrame());
}

void StartScreen::update(const double delta)
{
	_tankAnimator.update(delta);
}

void StartScreen::processInput(const std::array<bool, 350> & keys)
{
	if (!keys[GLFW_KEY_W] && !keys[GLFW_KEY_S])
	{
		_keyReleased = true;
	}
	if (_keyReleased)
	{
		if (keys[GLFW_KEY_W])
		{
			_keyReleased = false;
			--_currentMenuSelect;
			if (_currentMenuSelect < 0)
			{
				_currentMenuSelect = 2;
			}
		}
		else if (keys[GLFW_KEY_S])
		{
			_keyReleased = false;
			++_currentMenuSelect;
			if (_currentMenuSelect > 2)
			{
				_currentMenuSelect = 0;
			}
		}
	}

	if (keys[GLFW_KEY_ENTER])
	{
		switch (_currentMenuSelect)
		{
			case 0: {
				_game->startNewLevel(1);
				break;
			}
			default: {
				break;
			}
		}
	}
}

int StartScreen::getStateWidth() const
{
	return START_SCREEN_WIDTH;
}

int StartScreen::getStateHeight() const
{
	return START_SCREEN_HEIGHT;
}
}// namespace game