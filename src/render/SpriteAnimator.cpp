#include "SpriteAnimator.hpp"
#include "Sprite.hpp"

namespace render
{
SpriteAnimator::SpriteAnimator(const std::shared_ptr<Sprite> & sprite)
	: _sprite(sprite)
	, _currentFrame(0)
	, _currentFrameDuration(sprite->getFrameDuration(0))
	, _currentAnimationTime(0)
{
}

size_t SpriteAnimator::getCurrentFrame() const
{
	return _currentFrame;
}

void SpriteAnimator::update(const size_t delta)
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
}// namespace render