#pragma once

#include <array>

namespace game
{
class IGameState
{
public:
	virtual void render() const = 0;
	virtual void update(const double delta) = 0;
	virtual void processInput(const std::array<bool, 350> & keys) {}

	virtual int getStateWidth() const = 0;
	virtual int getStateHeight() const = 0;

	virtual ~IGameState() = default;
};
}// namespace game
