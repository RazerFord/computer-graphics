#pragma once

#include "../../render/SpriteAnimator.hpp"
#include "IGameState.hpp"
#include <glm/vec2.hpp>
#include <memory>
#include <string>
#include <vector>

namespace resources
{
class ResourceManager;
}

namespace render
{
class Sprite;
}

namespace game
{
class Game;

class StartScreen : public IGameState
{
private:
	bool _keyReleased;
	Game * _game;
	std::vector<std::pair<std::shared_ptr<render::Sprite>, glm::vec2>> _sprites;
	int _currentMenuSelect;
	std::pair<std::shared_ptr<render::Sprite>, glm::vec2> _menu;
	std::pair<std::shared_ptr<render::Sprite>, glm::vec2> _tank;
	render::SpriteAnimator _tankAnimator;

public:
	static constexpr int BLOCK_SIZE = 8;
	static constexpr int START_SCREEN_WIDTH = 15 * BLOCK_SIZE * 2;
	static constexpr int START_SCREEN_HEIGHT = 14 * BLOCK_SIZE * 2;
	static constexpr int MENU_WIDTH = 128;
	static constexpr int MENU_HEIGHT = 64;
	static constexpr int TANK_SIZE = BLOCK_SIZE * 2;

	StartScreen(const std::vector<std::string> & startScreenDescription, const resources::ResourceManager & manager, Game * game);

	virtual void render() const override;
	virtual void update(const double delta) override;
	virtual void processInput(const std::array<bool, 350> & keys) override;

	virtual int getStateWidth() const override;
	virtual int getStateHeight() const override;

	virtual ~StartScreen() override = default;
};
}// namespace game