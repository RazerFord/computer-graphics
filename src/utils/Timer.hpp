#pragma once

#include <functional>
namespace utils
{
class Timer
{
private:
	std::function<void()> _callback;
	double _timeLeft;
	bool _isRunning;

public:
	Timer();

	void update(const double delta);
	void start(const double duration);
	void setCallback(std::function<void()> callback);
};
}// namespace utils