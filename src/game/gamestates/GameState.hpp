#pragma once

namespace game
{
class GameState
{
public:
	virtual void render() const = 0;
	virtual void update(const double delta) = 0;
	virtual ~GameState() = default;

	virtual int getStateWidth() const = 0;
	virtual int getStateHeight() const = 0;
};
}// namespace game
