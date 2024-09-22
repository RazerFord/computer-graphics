#pragma once

#include "GameState.hpp"
#include <vector>
#include <string>
#include <memory>
#include <glm/vec2.hpp>

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
class StartScreen : public GameState
{
private:
	std::vector<std::pair<std::shared_ptr<render::Sprite>, glm::vec2>> _sprites;

public:
	static constexpr int BLOCK_SIZE = 8;
	static constexpr int START_SCREEN_WIDTH = 15 * BLOCK_SIZE * 2;
	static constexpr int START_SCREEN_HEIGHT = 14 * BLOCK_SIZE * 2;
    
	StartScreen(const std::vector<std::string>& startScreenDescription, const resources::ResourceManager& manager);

	virtual void render() const override;
	virtual void update(const double delta) override;

	virtual int getStateWidth() const override;
	virtual int getStateHeight() const override;

	virtual ~StartScreen() override = default;
};
}// namespace game