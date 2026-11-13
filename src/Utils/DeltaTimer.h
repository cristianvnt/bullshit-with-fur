#pragma once

#include <chrono>

class DeltaTimer
{
private:
	float _deltaTime = 0.f;
	std::chrono::time_point<std::chrono::high_resolution_clock> _lastFrameTime;

public:
	DeltaTimer() : _lastFrameTime(std::chrono::high_resolution_clock::now()) {}

	void Update();
	float GetDeltaTime() const { return _deltaTime; }
};
