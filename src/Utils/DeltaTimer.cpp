#include "DeltaTimer.h"

void DeltaTimer::Update()
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	_deltaTime = std::chrono::duration<float>(currentTime - _lastFrameTime).count();
	_lastFrameTime = currentTime;
}
