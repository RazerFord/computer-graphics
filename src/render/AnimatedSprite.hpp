#pragma once

#include "Sprite.hpp"
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace render
{
class Texture2D;
class ShaderProgram;

namespace details
{
struct State : std::pair<std::string, size_t> {
	const std::string & name() const { return first; }
	const size_t & duration() const { return second; }
};
}// namespace details

class AnimatedSprite : public Sprite
{
private:
	using StateStorage = std::map<std::string, std::vector<details::State>>;

	StateStorage _statesMap;
	size_t _currentFrame = 0;
	size_t _currentAnimationTime = 0;
	StateStorage::const_iterator _currentAnimationDurations = _statesMap.end();
	mutable bool _dirty = false;

public:
	using Sprite::Sprite;

	void insertState(const std::string & state, const std::vector<details::State> & subTextureDuration);

	void render() const override;

	void setState(const std::string & state);

	void update(const size_t delta);
};
}// namespace render