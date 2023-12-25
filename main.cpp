#include "Game.h"

int stringCompare(const char* password, char* userInput)
{
	int i = 0;
	for (i = 0; userInput[i] != '\0' && password[i] != '\0'; i++)
	{
		if (userInput[i] != password[i]) break;
	}

	return userInput[i] - password[i];
}


int main(int argc, char* argv[])
{
	Game game;

	if (argc >= 2)
	{
		game.DEBUG_MODE = stringCompare("DEBUGGER", argv[1]) == 0;

		if (game.DEBUG_MODE) printf("DEBUG MODE IS ENABLED");
	}

	game.run();

	return 0;
}