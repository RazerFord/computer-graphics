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
	using std::pair<std::string, size_t>::pair;

	const std::string & name() const { return first; }
	const size_t & duration() const { return second; }
};
}// namespace details

class AnimatedSprite : public Sprite
{
public:
	using States = std::vector<details::State>;

private:
	using StateStorage = std::map<std::string, States>;

	StateStorage _statesMap;
	size_t _currentFrame = 0;
	size_t _currentAnimationTime = 0;
	StateStorage::const_iterator _currentAnimationDurations = _statesMap.end();
	mutable bool _dirty = false;

public:
	using Sprite::Sprite;

	void insertState(const std::string & state, const std::vector<details::State> & subTextureDuration);

	void render(const glm::vec2 & position, const glm::vec2 & size, const float rotation) const override;

	void setState(const std::string & state);

	void update(const size_t delta);
};
}// namespace render