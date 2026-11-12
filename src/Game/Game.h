#pragma once

#pragma once

#include "Window.h"

class Game
{
private:
	Window _window;

public:
	Game() = default;
	~Game() = default;

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

	bool Init(const Settings& settings);
	void Run();
};