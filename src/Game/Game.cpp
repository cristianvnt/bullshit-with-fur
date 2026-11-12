#include "Game.h"

#include "Utils/Logger.h"

bool Game::Init(const Settings& settings)
{
	return _window.Init(settings.window);
}

void Game::Run()
{
	while (!_window.ShouldClose())
	{
		_window.PollEvents();

		// render
		GL_CHECK(glClearColor(0.1f, 0.2f, 0.15f, 1.f));
		GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

		_window.SwapBuffers();
	}
}
