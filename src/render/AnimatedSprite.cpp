#include "AnimatedSprite.hpp"
#include <iostream>
#include <vector>

namespace render
{
void AnimatedSprite::insertState(const std::string & state, const std::vector<details::State> & subTextureDuration)
{
	_statesMap[state] = subTextureDuration;
}

void AnimatedSprite::render() const
{
	
}

void AnimatedSprite::setState(const std::string & state)
{
	auto it = _statesMap.find(state);
	if (it == _statesMap.end())
	{
		std::cerr << "can't find animation state " << state << std::endl;
		return;
	}

	_currentAnimationTime = 0;
	_currentFrame = 0;
	_currentAnimationDurations = it;
}

void AnimatedSprite::update(const size_t delta)
{
	if (_currentAnimationDurations != _statesMap.end())
	{
		_currentAnimationTime += delta;
		const std::vector<details::State> animations = _currentAnimationDurations->second;
		if (size_t duration = animations[_currentFrame].duration(); _currentAnimationTime > duration)
		{
			_currentAnimationTime %= duration;
			_currentFrame = (_currentFrame + 1) % animations.size();
		}
	}
}
}// namespace render