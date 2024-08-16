#include "SpriteAnimator.hpp"
#include "Sprite.hpp"

namespace render
{
SpriteAnimator::SpriteAnimator(const std::shared_ptr<Sprite> & sprite)
	: _sprite(sprite)
	, _currentFrame(0)
	, _currentFrameDuration(sprite->getFrameDuration(0))
	, _currentAnimationTime(0)
	, _totalDuration(0)
{
	for (size_t i = 0; i < _sprite->getFramesCount(); i++)
	{
		_totalDuration += _sprite->getFrameDuration(i);
	}
}

size_t SpriteAnimator::getCurrentFrame() const
{
	return _currentFrame;
}

double SpriteAnimator::getTotalDuration() const
{
	return _totalDuration;
}

void SpriteAnimator::update(const double delta)
{
	_currentAnimationTime += delta;
	size_t countFrames = _sprite->getFramesCount();

	while (_currentAnimationTime >= _currentFrameDuration)
	{
		_currentAnimationTime -= _currentFrameDuration;
		_currentFrame = (_currentFrame + 1) % countFrames;
		_currentFrameDuration = _sprite->getFrameDuration(0);
	}
}

void SpriteAnimator::reset()
{
	_currentFrame = 0;
	_currentFrameDuration = _sprite->getFrameDuration(0);
	_currentAnimationTime = 0;
}
}// namespace render