#include "Game/Game.h"
#include "Utils/Settings.h"

int main()
{
	Settings settings = LoadSettings("settings.conf");

	Game game;
	if (!game.Init(settings))
		return 1;

	game.Run();
}
