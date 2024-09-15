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
	double _currentFrameDuration;
	double _currentAnimationTime;
	double _totalDuration;

public:
	SpriteAnimator(const std::shared_ptr<Sprite> & sprite);

	size_t getCurrentFrame() const;
	double getTotalDuration() const;

	void update(const double delta);

	void reset();
};
}// namespace render