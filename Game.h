#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"

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
	vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	bool fullscreen;

	//Frame rendering variables
	sf::Clock dtClock;
	double dt;

	stack<State*> states;

	map<string, int> supportedKeys;

	//Initializers
	void initVariables();
	void initGameWindow();
	void initStates();
	void initKeys();

	//Utilities
	string openINI(const char* file);
};

#endif