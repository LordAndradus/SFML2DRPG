#include "Game.h"

//This makes it, so that the release exe does not open the Windows console.
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main(int argc, char* argv[])
{
	Game game;

	if (argc >= 2)
	{
		game.DEBUG_MODE = strcmp("DEBUGGER", argv[1]) == 0;

		if (game.DEBUG_MODE) printf("DEBUG MODE IS ENABLED\n");
	}

	game.run();

	return 0;
}