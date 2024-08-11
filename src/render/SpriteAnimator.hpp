#pragma once

#include <memory>
namespace render
{
class Sprite;

class SpriteAnimator
{
private:
	std::shared_ptr<Sprite> _sprite;
	size_t _currentFrame;
	size_t _currentFrameDuration;
	size_t _currentAnimationTime;

public:
	SpriteAnimator(const std::shared_ptr<Sprite> & sprite);

	size_t getCurrentFrame() const;

	void update(const size_t delta);
};
}// namespace render