#include "Timer.hpp"

namespace utils
{
Timer::Timer()
	: _callback(nullptr)
	, _timeLeft(0)
	, _isRunning(false)
{}

void Timer::update(const double delta)
{
	if (_isRunning)
	{
		_timeLeft -= delta;

		if (_timeLeft <= 0)
		{
			_isRunning = false;
			_callback();
		}
	}
}

void Timer::start(const double duration)
{
	_timeLeft = duration;
	_isRunning = true;
}

void Timer::setCallback(std::function<void()> callback)
{
	_callback = std::move(callback);
}
}// namespace utils