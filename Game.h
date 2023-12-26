#ifndef GAME_H
#define GAME_H

#include "GameState.h"

using namespace std;

class Game
{
public:
	//Constructor/Destructor
	Game();
	virtual ~Game();

	bool DEBUG_MODE = 0;

	//Regulator
	void endApplication();

	//Updates
	void updateDt();
	void updateSFMLEvents();
	void update();

	//Render
	void render();

	//Core loop
	void run();

private:
	//Hidden variables
	sf::RenderWindow *window;
	sf::Event sfEvent;

	//Frame rendering variables
	sf::Clock dtClock;
	double dt;

	stack<State*> states;

	map<string, int> supportedKeys;

	//Initializers
	void initGameWindow();
	void initStates();
	void initKeys();

	//Utilities
	string openINI(const char* file);
};

#endif